#include "UART.h"

int main()
{
	std::vector<std::string> set = UART::searchPorts();

	for (auto s : set)
	{
		std::cout << s << std::endl;
	}

	UART com7;
	com7.open();
	
	while (1)
	{
		std::string f;
		std::cin >> f;
		com7.sendSimpleMessage(f);
	}

	return 0;
}