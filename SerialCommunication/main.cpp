#include "UART.h"

int main()
{
	std::vector<std::string> set = UART::searchPorts();

	for (auto s : set)
	{
		std::cout << s << std::endl;
	}

	return 0;
}