#include "InternetSocket.h"
#include "utils.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

namespace aracne
{
	InternetSocket::InternetSocket()
	{
		socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd < 0)
		{
			error("Could not create Internet Socket");
		}
	}

	int InternetSocket::SendRequest(HttpRequest &request, char *response, int max)
	{
		std::string& hostname = request.header.at("Host:");
		hostent* host = gethostbyname(hostname.c_str());
		if (host == NULL || host->h_addr_list == NULL)
		{
			error("Could not get host address by name");
		}
		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(80);
		// Address comes from DNS lookup
		memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
		if (connect(socket_fd, (sockaddr *) &addr, sizeof(addr)) < 0)
		{
			error("Could not connect to server");
		}

		// Connection estabilished, sending HTTP request
		std::string request_str = request.ToString();
		if (write(socket_fd, request_str.c_str(), request_str.length()) < 0)
		{
			error("Could not write data to socket");
		}

		int n = read(socket_fd, response, max);
		if (n < 0)
		{
			error("Could not read response");
		}
		
		return n;
	}

}