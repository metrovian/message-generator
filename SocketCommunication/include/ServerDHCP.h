#include "UDP.h"

class ServerDHCP : public UDP
{
protected: /* data */
	std::map<std::string, std::string> band;

public: /* constructor */
	ServerDHCP();
	~ServerDHCP();

protected: /* band */
	bool insert(std::string _ip);
	bool erase(std::string _ip);

protected: /* address */
	bool leaseHostAddress(std::string _ip, std::string _mac);
	bool releaseHostAddress(std::string _ip, std::string _mac);
	
protected: /* virtual */
	virtual void processReceivedMessage(std::string _msg, uint16_t _port);
};