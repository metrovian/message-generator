#include "ServerDHCP.h"

ServerDHCP::ServerDHCP() : UDP()
{
	startReceiveThread(67);
}

ServerDHCP::~ServerDHCP()
{
	stopThread(67);
}

bool ServerDHCP::insert(std::string _ip)
{
	band.insert(std::make_pair(_ip, std::string()));
}

bool ServerDHCP::erase(std::string _ip)
{
	band.erase(_ip);
}

bool ServerDHCP::leaseHostAddress(std::string _ip, std::string _mac)
{
	return false;
}

bool ServerDHCP::releaseHostAddress(std::string _ip, std::string _mac)
{
	return false;
}

void ServerDHCP::processReceivedMessage(std::string _msg, uint16_t _port)
{
	std::cerr << "[Host : " << _port << "] " << _msg << std::endl;
}
