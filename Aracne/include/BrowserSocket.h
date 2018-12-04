#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdint>

namespace aracne {

#define MEGA (1024 * 1024)

class BrowserSocket {
 private:
  struct sockaddr_in server_address = {0}, client_address;
  int welcome_socket_fd = 0, client_socket_fd = 0;
  char buffer[1 * MEGA];

 public:
  BrowserSocket() = default;
  ~BrowserSocket();
  void Initialize(uint16_t port);
  void AwaitConnection();
  int ReadRequest(char *buffer, int max);
  void SendResponse(char *buffer, int length);
};

}  // namespace aracne