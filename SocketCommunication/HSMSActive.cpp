#include "HSMSActive.h"

bool HSMSActive::connect(std::string _ip, uint16_t _port)
{
	if (state == HSMS_STATE::CONNECTED) return false;

	ip = _ip;
	port = _port;

	bool ret = TCPClient::connect();

	if (ret) state = HSMS_STATE::CONNECTED;
	return ret;
}

bool HSMSActive::disconnect()
{
	if (state == HSMS_STATE::NONE) return false;

	bool ret = TCPClient::disconnect();

	if (ret) state = HSMS_STATE::NONE;
	return ret;
}

bool HSMSActive::sendRequest(HSMS_SESSION _ses)
{
	if (state != HSMS_STATE::SELECTED) return false;

	std::string msg;
	msg.resize(10);

	msg[5] = static_cast<char>(_ses);
	msg[6] = static_cast<char>(trans >> 6);
	msg[7] = static_cast<char>((trans >> 4) & 0xFF);
	msg[8] = static_cast<char>((trans >> 2) & 0xFF);
	msg[9] = static_cast<char>(trans & 0xFF);

	pends.insert(++trans);

	return sendSimpleMessage(msg);
}

bool HSMSActive::sendResponse(HSMS_SESSION _ses, uint32_t _trans)
{
	if (state != HSMS_STATE::SELECTED) return false;

	std::string msg;
	msg.resize(10);

	msg[5] = static_cast<char>(_ses);
	msg[6] = static_cast<char>(_trans >> 6);
	msg[7] = static_cast<char>((_trans >> 4) & 0xFF);
	msg[8] = static_cast<char>((_trans >> 2) & 0xFF);
	msg[9] = static_cast<char>(_trans & 0xFF);

	return sendSimpleMessage(msg);
}

void HSMSActive::processReceivedMessage(std::string _msg)
{
	std::vector<BYTE> frame;

	for (char data : _msg)
	{
		frame.push_back(static_cast<BYTE>(data));
	}

	if (frame.size() < 9) return;

	uint32_t rans = static_cast<uint32_t>(frame[6] << 6);
	rans += static_cast<uint32_t>(frame[7] << 4);
	rans += static_cast<uint32_t>(frame[8] << 2);
	rans += static_cast<uint32_t>(frame[9]);

	if (frame[2] == 0x00)
	{
		switch (static_cast<HSMS_SESSION>(frame[5]))
		{

		case HSMS_SESSION::SELECT_REQ:
		{
			state = HSMS_STATE::SELECTED;
			pends.erase(rans);
			sendResponse(HSMS_SESSION::SELECT_RSP, rans);
			break;
		}

		case HSMS_SESSION::SELECT_RSP:
		{
			state = HSMS_STATE::SELECTED;
			pends.erase(rans);
			break;
		}
			
		case HSMS_SESSION::DESELECT_REQ:
		{
			state = HSMS_STATE::CONNECTED;
			pends.erase(rans);
			sendResponse(HSMS_SESSION::DESELECT_RSP, rans);
			break;
		}

		case HSMS_SESSION::DESELECT_RSP:
		{
			state = HSMS_STATE::CONNECTED;
			pends.erase(rans);
			break;
		}

		case HSMS_SESSION::LINKTEST_REQ:
		{
			pends.erase(rans);
			sendResponse(HSMS_SESSION::LINKTEST_RSP, rans);
			break;
		}

		case HSMS_SESSION::LINKTEST_RSP:
		{
			pends.erase(rans);
			break;
		}

		default:
		{
			sendResponse(HSMS_SESSION::REJECT_REQ, rans);
			break;
		}

		}

		return;
	}

	if (frame[5] == 0x00)
	{
		return;
	}
}
