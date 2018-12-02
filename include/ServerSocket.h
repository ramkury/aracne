#include <cstdint>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace aracne
{

#define MEGA (1024 * 1024)

class ServerSocket
{
  private:
	struct sockaddr_in server_address = {0}, client_address;
	int welcome_socket_fd = 0, client_socket_fd = 0;
	char buffer[1 * MEGA];

  public:
	ServerSocket() = default;
	~ServerSocket();
	void Initialize(uint16_t port);
	void AwaitConnection();
	int ReadRequest(char *buffer, int max);
};

} // namespace aracne