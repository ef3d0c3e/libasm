#include <libasm.h>

#include <assert.h>
#include <string.h>

#define test(str)                                                                                \
	do {                                                                                         \
		char buf[4096];                                                                          \
		memset(buf, 1, sizeof buf);                                                              \
		ft_strcpy(buf, str);                                                                     \
		assert(strcmp(buf, str) == 0);                                                               \
	} while (0)

void
test_strcpy(void)
{
	test("");
	test("A");
	test("AB");
	test("ABCDEF");
	test("lorem ipsum dolor sit amet");
}
