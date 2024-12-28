#include "ServerHTTP.h"

HTTP_REQUEST ServerHTTP::parseRequestMessage(std::string _msg)
{
	HTTP_REQUEST ret;

	std::istringstream ss(_msg);
	std::string line;

	if (!std::getline(ss, line)) return ret;

	std::istringstream ls(line);
	ls >> ret.method >> ret.url >> ret.version;

	while (std::getline(ss, line) && (line != "\r"))
	{
		size_t pos = line.find(": ");

		if (pos != std::string::npos)
		{
			std::string prop = line.substr(0, pos);
			std::string val = line.substr(2 + pos);

			if (!val.empty() && (val.back() == '\r'))
			{
				val.pop_back();
			}

			ret.header[prop] = val;
		}
	}

	if (ret.header.find("Content-Length") != ret.header.end())
	{
		int len = std::stoi(ret.header["Content-Length"]);
		ret.body.resize(len);
		ss.read(&ret.body[0], len);
	}

	return ret;
}

bool ServerHTTP::open()
{
	port = 80;
	return ServerTCP::open();
}

bool ServerHTTP::close()
{
	return ServerTCP::close();
}

void ServerHTTP::processReceivedMessage(std::string _msg, uint64_t _idx)
{
	HTTP_REQUEST req = parseRequestMessage(_msg);

	std::cerr << "[Client " << _idx << "] " << "Request : " << req.method << " " << req.url << " " << req.version << std::endl;
}
