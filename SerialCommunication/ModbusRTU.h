#pragma once
#include "UART.h"

class ModbusRTU : public UART
{
protected: /* config */
	DWORD baud = 9600;

protected: /* check */
	WORD calcCRC(std::vector<BYTE> _frame);

public: /* send */
	bool sendRequest(std::vector<BYTE> _frame);

protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg);
};