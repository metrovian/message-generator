#pragma once
#include "UDP.h"
#include "FrameSNMP.h"

class ServerSNMP : public UDP
{
public: /* constructor */
	ServerSNMP();
	~ServerSNMP();

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg, uint16_t _port);
};