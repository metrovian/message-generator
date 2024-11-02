#pragma once
#include "TCPClient.h"
#include "Predefined.h"

class HSMSActive : public TCPClient
{
protected: /* state */
	HSMS_STATE state = HSMS_STATE::NONE;

public: /* constructor */
	HSMSActive();
	~HSMSActive() = default;

public: /* connection */
	bool connect(std::string _ip, uint16_t _port);
	bool disconnect();

public: /* send */
	bool sendRequest(HSMS_SESSION _ses);
};