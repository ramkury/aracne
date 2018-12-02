#include "ServerSocket.h"
#include <string>
#include <cstring>
#include <iostream>

namespace aracne
{

void ServerSocket::Initialize(uint16_t port)
{
	if ((welcome_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << std::string("Could not create socket") << std::endl;
		exit(-1);
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);

	int bindres = bind(welcome_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address));
	if (bindres < 0)
	{	
		std::cout << "Could not bind server socket to port " << port << std::endl;
		exit(-2);
	}

	listen(welcome_socket_fd, 1);

	std::cout << "Listening on port " << port << std::endl;
}

void ServerSocket::AwaitConnection()
{
	socklen_t length = sizeof(client_address);
	client_socket_fd = accept(welcome_socket_fd, (sockaddr *)&client_address, &length);

	if (client_socket_fd < 0)
	{
		throw std::string("Error accepting connection");
	}

	std::cout
		<< "Accepted connection from " << inet_ntoa(client_address.sin_addr)
		<< " on port " << ntohs(client_address.sin_port)
		<< std::endl;
}

} // namespace aracne