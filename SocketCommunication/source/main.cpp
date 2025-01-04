#include "../include/ServerHTTP.h"
#include "../include/ClientHTTP.h"

int main()
{
	ServerHTTP http;
	http.open();
	getchar();
	http.close();
	getchar();
	return 0;
}