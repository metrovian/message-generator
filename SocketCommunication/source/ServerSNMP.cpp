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

void ServerSNMP::processReceivedMessage(std::string _msg, uint16_t _port)
{
}
