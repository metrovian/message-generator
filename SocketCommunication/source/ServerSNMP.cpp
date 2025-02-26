#include "ServerSNMP.h"

ServerSNMP::ServerSNMP()
{
	startReceiveThread(161);
	startReceiveThread(162);
}

ServerSNMP::~ServerSNMP()
{
	stopThread(161);
	stopThread(162);
}

std::string ServerSNMP::encodeNumberASN1(int32_t _num)
{
	std::string ret;

	ret.push_back(0x02);
	ret.push_back(0x04);

	ret.push_back(static_cast<char>(0xFF & (_num >> 24)));
	ret.push_back(static_cast<char>(0xFF & (_num >> 16)));
	ret.push_back(static_cast<char>(0xFF & (_num >> 8)));
	ret.push_back(static_cast<char>(0xFF & (_num >> 0)));

	return ret;
}

std::string ServerSNMP::encodeMessageASN1(std::string _str)
{
	std::string ret;

	ret.push_back(0x04);
	ret.push_back(_str.size());

	ret += _str;

	return ret;
}

std::string ServerSNMP::encodeFrameASN1(SNMP_SESSION _ses, SNMP_FRAME _msg)
{
	std::string ret;

	uint64_t sofs;
	uint64_t bofs;
	uint64_t cofs;

	ret += encodeNumberASN1(_msg.version);
	ret += encodeMessageASN1(_msg.community);

	ret.push_back(static_cast<char>(_ses));
	ret.push_back(0x00);

	sofs = ret.size();

	ret += encodeNumberASN1(_msg.id);
	ret += encodeNumberASN1(_msg.ers);
	ret += encodeNumberASN1(_msg.eri);

	ret.push_back(0x30);
	ret.push_back(0x00);

	bofs = ret.size();

	for (const auto& pair : _msg.binds) 
	{
		ret.push_back(0x30);
		ret.push_back(0x00);

		cofs = ret.size();

		ret.push_back(0x06);
		ret.push_back(pair.first.size());

		ret += pair.first;

		ret.push_back(0x05);
		ret.push_back(pair.second.size());

		ret += pair.second;

		ret[cofs - 1] = ret.size() - cofs;
	}

	ret[sofs - 1] = ret.size() - sofs;
	ret[bofs - 1] = ret.size() - bofs;

	ret.insert(ret.begin(), ret.size());
	ret.insert(ret.begin(), 0x30);

	return ret;
}

bool ServerSNMP::sendRequestMessage(std::string _ip, SNMP_SESSION _ses, SNMP_FRAME _msg)
{
	return sendSimpleMessage(encodeFrameASN1(_ses, _msg), _ip, 161);
}

void ServerSNMP::processReceivedMessage(std::string _msg, uint16_t _port)
{
}
