#include <errno.h>
#include <libasm.h>

#include <assert.h>
#include <stdlib.h>

void
test_calloc(void)
{
	void *p1 = ft_calloc(64, 1);
	assert(p1 != NULL);
	free(p1);

	errno = 0;
	void *p2 = ft_calloc(0xFFFFFFFF, 0xFFFFFFFF);
	assert(errno == ENOMEM);
	assert(p2 == NULL);

	/* Needs memory overcommit
	size_t s = 0xFFFFFFFF * 0xFFFFFFFF;
	void *p3 = malloc(s);
	assert(p3 != NULL);
	free(p3); */
}

