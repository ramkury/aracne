#include "BrowserSocket.h"
#include "InternetSocket.h"
#include "HttpRequest.h"
#include <iostream>

#define BUF_SIZE (1024 * 1024)

using namespace aracne;

int main(int argc, char const *argv[])
{
	char *buffer = new char[BUF_SIZE];
	std::cout << "Starting" << std::endl;
	int port = argc > 1 ? atoi(argv[argc - 1]) : 8228;
	BrowserSocket ss;
	ss.Initialize(port);
	while (true)
	{
		ss.AwaitConnection();

		int n = ss.ReadRequest(buffer, BUF_SIZE);
		if (n < 5)
		{
			continue;
		}
		buffer[n] = '\0';
		std::cout << "Request:" << std::endl
				  << buffer << std::endl;

		std::cout.flush();

		HttpRequest request(buffer);

		// std::cout << "Rebuilt request: " << std::endl << request.ToString() << std::endl;

		InternetSocket is;
		int response_size = is.SendRequest(request, buffer, BUF_SIZE);

		buffer[response_size] = '\0';
		std::cout << "Response: " << std::endl
				  << buffer << std::endl;

		ss.SendResponse(buffer, response_size);
	}

	delete[] buffer;

	return 0;
}
