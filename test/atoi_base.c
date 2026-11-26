#include <libasm.h>

#include <assert.h>
#include <limits.h>

void
test_atoi_base(void)
{
	/* valid bases */
	assert(ft_atoi_base("42", "0123456789") == 42);
	assert(ft_atoi_base("ff", "0123456789abcdef") == 255);
	assert(ft_atoi_base("101", "01") == 5);
	assert(ft_atoi_base("zyx", "xyz") == 2 * 9 + 1 * 3 + 0);
	assert(ft_atoi_base("0", "01") == 0);
	assert(ft_atoi_base("", "01") == 0);

	/* whitespace, sign, trailing garbage */
	assert(ft_atoi_base(" \t\n\v\f\r-2a", "0123456789abcdef") == -42);
	assert(ft_atoi_base("+7", "01234567") == 7);
	assert(ft_atoi_base("12g34", "0123456789abcdef") == 0x12);
	assert(ft_atoi_base("--1", "0123456789") == 0);
	assert(ft_atoi_base("- 1", "0123456789") == 0);

	/* int limits */
	assert(ft_atoi_base("2147483647", "0123456789") == INT_MAX);
	assert(ft_atoi_base("-2147483648", "0123456789") == INT_MIN);

	/* invalid bases */
	assert(ft_atoi_base("1", "") == 0);
	assert(ft_atoi_base("1", "1") == 0);
	assert(ft_atoi_base("1", "0120") == 0);
	assert(ft_atoi_base("1", "01+") == 0);
	assert(ft_atoi_base("1", "01-") == 0);
	assert(ft_atoi_base("1", "01 ") == 0);
	assert(ft_atoi_base("1", "0\t1") == 0);
}
