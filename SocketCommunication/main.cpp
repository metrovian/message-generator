#include "TCPServer.h"

int main()
{
	TCPServer t;
	t.open();

	while (1)
	{
		getchar();
		t.sendSimpleMessage("hello");
	}
	return 0;
}