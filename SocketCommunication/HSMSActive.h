#pragma once
#include "TCPClient.h"
#include "Predefined.h"

class HSMSActive : public TCPClient
{
protected: /* state */
	HSMS_STATE state = HSMS_STATE::NONE;

protected: /* transaction */
	uint32_t trans = static_cast<uint32_t>(rand());
	std::set<uint32_t> pends;

public: /* connection */
	bool connect(std::string _ip, uint16_t _port);
	bool disconnect();

public: /* send */
	bool sendRequest(HSMS_SESSION _ses);
	bool sendResponse(HSMS_SESSION _ses, uint32_t _trans);

protected: /* thread */
	bool startLinkTestThread();
	bool stopThread();

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg);
};