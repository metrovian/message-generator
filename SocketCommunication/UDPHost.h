#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include <thread>
#include <iostream>

class UDPHost
{
protected: /* socket */
	SOCKET host;

protected: /* flag */
	bool flag = false;

public: /* constructor */
	UDPHost();
	~UDPHost();

public: /* send */
	bool sendSimpleMessage(std::string _msg, std::string _ip, uint16_t _port);

private: /* thread */
	bool startReceiveThread();
	bool stopThread();

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg);
};