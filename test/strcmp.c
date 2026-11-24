#include <libasm.h>

#include <assert.h>

void
test_strcmp(void)
{
	assert(ft_strcmp("", "") == 0);
	assert(ft_strcmp("a", "") == 'a');
	assert(ft_strcmp("", "a") == -(int)'a');
}
