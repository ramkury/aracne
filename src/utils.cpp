#include <cstdio>
#include <cstdlib>

namespace aracne
{

void error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(-1);
}

} // namespace aracne