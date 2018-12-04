#include "InternetSocket.h"
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "utils.h"
#include <errno.h>

namespace aracne {
InternetSocket::InternetSocket() {
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    error("Could not create Internet Socket");
  }
}

void InternetSocket::UpdateRequest(HttpRequest &request) {
  request.header["Accept-Encoding:"] = "identity";
  request.header["Connection:"] = "close";
}

int InternetSocket::SendRequest(HttpRequest &request, char *response, int max) {
  std::string &hostname = request.header.at("Host:");
  hostent *host = gethostbyname(hostname.c_str());
  if (host == NULL || host->h_addr_list == NULL) {
    error("Could not get host address by name");
  }
  sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  // Address comes from DNS lookup
  memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
  while (connect(socket_fd, (sockaddr *)&addr, sizeof(addr)) < 0) {
      fprintf(stderr, "Errno: %d\t", errno);
      if(errno == 106) {
          socket_fd = socket(AF_INET, SOCK_STREAM, 0);
          if (socket_fd < 0) {
            error("Could not create Internet Socket");
          }
      } else {
          error("Could not connect to server");
      }
  }

  // Connection estabilished, sending HTTP request
  UpdateRequest(request);
  std::string request_str = request.ToString();
  if (write(socket_fd, request_str.c_str(), request_str.length()) < 0) {
    error("Could not write data to Internet Socket");
  }

  int n = 0, total = 0;
  while ((n = read(socket_fd, response + total, max - total)) > 0) {
    total += n;
  }

  if (n < 0) {
    error("Could not read response");
  }

  if (total >= max) {
    error("InternetSocket: buffer overflow");
  }

  close(socket_fd);

  response[total] = '\0';

  return total;
}

}  // namespace aracne
