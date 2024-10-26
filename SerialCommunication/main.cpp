#include "UART.h"
#include "ModbusRTU.h"

int main()
{
	ModbusRTU com7;
	com7.open();
	
	while (1)
	{
		com7.sendRequest({ 0x01, 0x01, 0x01, 0x01 });
		std::cout << "sent" << std::endl;
		getchar();
	}

	return 0;
}