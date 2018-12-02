#pragma once

#include <string>
#include <map>

namespace aracne
{

class HttpRequest
{
public:
	std::string method;
	std::string url;
	std::string version;
	std::map<std::string, std::string> header;
	HttpRequest();
	HttpRequest(char * request);
	void Parse(char * request);
	std::string ToString();
};

} // namespace aracne