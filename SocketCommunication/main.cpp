#include "HSMSActive.h"
#include "HSMSPassive.h"
#include "TCPServer.h"
int main()
{
	HSMSActive t;
	HSMSPassive s;
	s.open(8080);
	getchar();
	t.connect("127.0.0.1", 8080);
	
	while (1)
	{
		getchar();
		t.sendRequest(HSMS_SESSION::SELECT_REQ);
	}
	return 0;
}