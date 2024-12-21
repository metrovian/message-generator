#include "HSMSActive.h"
#include "HSMSPassive.h"
#include "TCPServer.h"
#include "TCPClient.h"
int main()
{
	HSMSActive t;
	HSMSPassive s;
	s.open(1235);
	Sleep(100);
	t.connect("127.0.0.1", 1235);
	
	while (1)
	{
		Sleep(10000);
		s.sendRequest(HSMS_SESSION::SELECT_REQ, 0);
		s.sendData("HSMS_TEST", 0);
	}
	return 0;
}