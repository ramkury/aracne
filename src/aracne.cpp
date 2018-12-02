#include "ServerSocket.h"
#include "HttpRequest.h"
#include <iostream>

using namespace aracne;

int main(int argc, char const *argv[])
{
	char buffer[1024 * 1024];
	std::cout << "Starting" << std::endl;
	int port = argc > 1 ? atoi(argv[argc - 1]) : 8228;
	ServerSocket ss;
	ss.Initialize(port);
	ss.AwaitConnection();
	int n = ss.ReadRequest(buffer, sizeof(buffer));
	buffer[n] = '\0';
	std::cout << "Request:" << std::endl << buffer << std::endl;

	HttpRequest request(buffer);

	std::cout << "Rebuilt request: " << std::endl << request.ToString() << std::endl;

	std::cin.get();
	return 0;
}
