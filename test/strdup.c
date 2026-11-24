#include <libasm.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define test(str)                                                                                \
	do {                                                                                         \
		char *dup = ft_strdup(str); \
		const size_t len = strlen(str); \
		assert(memcmp(str, dup, len) == 0); \
		free(dup); \
	} while (0)

void
test_strdup(void)
{
	test("");
	test("A");
	test("AB");
	test("ABCDEF");
	test("lorem ipsum dolor sit amet");
	test("\001\002\003");
}
