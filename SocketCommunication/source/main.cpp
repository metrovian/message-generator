#include "ServerDHCP.h"

int main()
{
	ServerDHCP s("192.168.0.1", "255.255.0.0");

	s.insert("192.168.0.100");
	s.insert("192.168.0.101");
	s.insert("192.168.0.102");

	while (1);

	return 0;
}