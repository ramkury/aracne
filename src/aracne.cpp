#include "ServerSocket.h"
#include <iostream>

using namespace aracne;

int main(int argc, char const *argv[])
{
	std::cout << "Starting" << std::endl;
	int port = argc > 1 ? atoi(argv[argc - 1]) : 8228;
	ServerSocket ss;
	ss.Initialize(port);
	ss.AwaitConnection();
	return 0;
}
