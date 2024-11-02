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
