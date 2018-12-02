#include "HttpRequest.h"
#include <cstring>
#include <vector>
#include <sstream>

namespace aracne
{

HttpRequest::HttpRequest()
{
}

HttpRequest::HttpRequest(char *request)
{
	Parse(request);
}

void HttpRequest::Parse(char *request)
{
	method = strtok(request, " ");
	url = strtok(NULL, " ");
	version = strtok(NULL, "\r\n");

	char *field_name, *field_value;
	while ((field_name = strtok(NULL, " ")) && (field_value = strtok(NULL, "\r\n"))) {
		header[field_name + 1] = field_value;
	}
}

std::string HttpRequest::ToString()
{
	std::ostringstream res;
	res << method << " " << url << " " << version << "\r\n";
	for (auto& field : header)
	{
		res << field.first << " " << field.second << "\r\n";
	}
	res << "\r\n";

	return res.str();
}

} // namespace aracne
