#include <libasm.h>

#include <assert.h>
#include <string.h>

void test_strlen(void)
{
	assert(ft_strlen("") == 0);
	assert(ft_strlen("A") == 1);
	assert(ft_strlen("ABCDEF") == 6);
	char buf[4096];
	memset(buf, 'a', 4000);
	buf[4000] = 0;
	assert(ft_strlen(buf) == 4000);
}
