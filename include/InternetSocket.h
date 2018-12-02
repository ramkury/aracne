#pragma once
#include "HttpRequest.h"

namespace aracne
{
class InternetSocket
{
  private:
	int socket_fd = -1;
  public:
	InternetSocket() = default;
	int SendRequest(HttpRequest &request, char *response, int max);
};
} // namespace aracne