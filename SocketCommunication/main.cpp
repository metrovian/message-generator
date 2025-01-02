#include "ServerHTTP.h"
#include "ClientHTTP.h"

int main()
{
	ServerHTTP http;
	http.open();
	getchar();
	http.close();
	getchar();
	return 0;
}