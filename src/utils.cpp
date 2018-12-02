#include <cstdio>
#include <cstdlib>

namespace aracne
{

void error(const char *message)
{
	perror(message);
	exit(-1);
}

} // namespace aracne