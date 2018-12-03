#include "BrowserSocket.h"
#include "utils.h"
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace aracne
{

void BrowserSocket::Initialize(uint16_t port)
{
	if ((welcome_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << std::string("Could not create socket") << std::endl;
		exit(-1);
	}

	server_address.sin_family = AF_INET;
	inet_aton("127.0.0.1", (in_addr*) &server_address.sin_addr.s_addr);
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

void BrowserSocket::AwaitConnection()
{
	socklen_t length = sizeof(client_address);
	client_socket_fd = accept(welcome_socket_fd, (sockaddr *)&client_address, &length);

	if (client_socket_fd < 0)
	{
		std::cout << "Error accepting connection" << std::endl;
		exit(-3);
	}

	std::cout
		<< "Accepted connection from " << inet_ntoa(client_address.sin_addr)
		<< " on port " << ntohs(client_address.sin_port)
		<< std::endl;
}

int BrowserSocket::ReadRequest(char * buffer, int max)
{
	int n = read(client_socket_fd, buffer, max);
	if (n < 0)
	{
		std::cout << "Error reading from socket" << std::endl;
		exit(-4);
	}

	if (n >= max)
	{
		error("BrowserSocket: buffer overflow");
	}
	return n;
}

void BrowserSocket::SendResponse(char * buffer, int length)
{
	if (write(client_socket_fd, buffer, length) < 0)
	{
		error("Could not write response to Browser Socket");
	}
}

BrowserSocket::~BrowserSocket()
{
	if (welcome_socket_fd) close(welcome_socket_fd);
	if (client_socket_fd) close(client_socket_fd);
}

} // namespace aracne