#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <string>
#include <vector>
#include <thread>
#include <iostream>

class UDP
{
protected: /* socket */
	SOCKET host;

protected: /* config */
	std::string ip = "127.0.0.1";
	uint16_t port = 8080;

protected: /* flag */
	bool flag = false;

public: /* send */
	bool sendSimpleMessage(std::string _msg);

private: /* thread */
	bool startReceiveThread();
	bool stopThread();
};