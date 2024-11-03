#include "HSMSActive.h"
#include "HSMSPassive.h"
#include "TCPServer.h"
#include "TCPClient.h"
int main()
{
	HSMSActive t;
	HSMSPassive s;
	s.open(8082);
	Sleep(1000);
	t.connect("127.0.0.1", 8082);
	
	while (1)
	{
		Sleep(1000);
		s.sendRequest(HSMS_SESSION::SELECT_REQ, 0);
	}
	return 0;
}