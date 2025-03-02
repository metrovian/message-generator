#include "ServerSNMP.h"
#include "ServerDHCP.h"

int main()
{
	ServerSNMP s;

	SNMP_FRAME fr;

	fr.community = "public";
	fr.id = 12345;
	fr.binds.push_back(std::make_pair(std::string{ 0x2B, 0x06, 0x01, 0x02, 0x01 }, ""));

	s.sendRequestMessage("192.168.50.102", SNMP_SESSION::GET_REQUEST, fr);

	return 0;
}