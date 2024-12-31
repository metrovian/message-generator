#include "ServerHTTP.h"
#include "ClientHTTP.h"

int main()
{
	ServerHTTP http;
	http.open();
	getchar();
	ClientHTTP cc;
	cc.connect("127.0.0.1");
	getchar();
	cc.sendRequestMessage({ "GET", "/", "HTTP/1.1" });
	getchar();
	http.close();
	getchar();
	return 0;
}