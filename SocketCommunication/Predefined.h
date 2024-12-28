#pragma once
#include <string>
#include <unordered_map>

constexpr int BUFFER_SIZE = 1024;
constexpr int HSMS_TIMEOUT = 100;

struct HTTP_REQUEST
{
	std::string url;
	std::string method;
	std::string version;
	std::string body;
	std::unordered_map<std::string, std::string> header;
};

enum class HSMS_STATE
{
	NONE,
	CONNECTED,
	SELECTED,
};

enum class HSMS_SESSION
{
	DATA,
	SELECT_REQ,
	SELECT_RSP,
	DESELECT_REQ,
	DESELECT_RSP,
	LINKTEST_REQ,
	LINKTEST_RSP,
	REJECT_REQ,
	SEPARATE_REQ,
};