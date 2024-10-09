#include "TCPServer.h"
#include "TCPClient.h"
#include "UDPHost.h"

int main()
{
	UDPHost t;

	while (1)
	{
		getchar();
		t.sendSimpleMessage("hello", "127.0.0.1", 8080);
	}
	return 0;
}