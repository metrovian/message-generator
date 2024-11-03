#include "HSMSActive.h"
#include "HSMSPassive.h"
#include "TCPServer.h"
#include "TCPClient.h"
int main()
{
	WSACleanup();
	HSMSActive t;
	HSMSPassive s;
	//TCPServer s;
	//TCPClient t;
	//s.open(8082);
	//s.open();
	Sleep(1000);
	t.connect("127.0.0.1", 8082);
	//t.connect();
	
	while (1)
	{
		Sleep(1000);
		t.sendRequest(HSMS_SESSION::SELECT_REQ);
	}
	return 0;
}