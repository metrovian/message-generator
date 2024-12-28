#pragma once
#include "ServerTCP.h"
#include "Predefined.h"

class ServerHTTP : public ServerTCP
{
protected: /* parse */
	HTTP_REQUEST parseRequestMessage(std::string _msg);

public: /* connection */
	bool open();
	bool close();

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg, uint64_t _idx);
};