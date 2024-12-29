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

protected: /* send */
	bool sendResponseMessage(HTTP_RESPONSE _msg, uint64_t _idx);

protected: /* recv */
	bool processReceivedGet(HTTP_REQUEST _msg);
	bool processReceivedPost(HTTP_REQUEST _msg);
	bool processReceivedPut(HTTP_REQUEST _msg);
	bool processReceivedDelete(HTTP_REQUEST _msg);

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg, uint64_t _idx);
};