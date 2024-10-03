#include "TCPServer.h"
#include "TCPClient.h"

int main()
{
	TCPClient t;
	t.connect();

	while (1)
	{
		getchar();
		t.sendSimpleMessage("hello");
	}
	return 0;
}