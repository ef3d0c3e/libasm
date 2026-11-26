#define _DEFAULT_SOURCE
#include <libasm.h>

#include <sys/mman.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/* every alignment x length x match position, against libc memchr */
static void
test_exhaustive(void)
{
	unsigned char buf[128];

	for (size_t off = 0; off < 32; ++off) {
		for (size_t n = 0; n <= 80; ++n) {
			unsigned char *s = buf + off;
			memset(buf, 'x', sizeof buf);

			/* no match inside, but matches right before and after */
			if (off > 0)
				s[-1] = 'A';
			s[n] = 'A';
			assert(ft_simd_memchr(s, 'A', n) == memchr(s, 'A', n));

			/* single match at every position, then two matches */
			for (size_t pos = 0; pos < n; ++pos) {
				memset(buf, 'x', sizeof buf);
				s[pos] = 'A';
				assert(ft_simd_memchr(s, 'A', n) == s + pos);
				if (pos + 1 < n) {
					s[n - 1] = 'A';
					assert(ft_simd_memchr(s, 'A', n) == s + pos);
				}
			}
		}
	}
}

/* c is converted to unsigned char */
static void
test_char_conversion(void)
{
	unsigned char s[] = { 1, 0, 0xFF, 'A', 0x80 };

	assert(ft_simd_memchr(s, 0, sizeof s) == s + 1);
	assert(ft_simd_memchr(s, -1, sizeof s) == s + 2);
	assert(ft_simd_memchr(s, 0x100 + 'A', sizeof s) == s + 3);
	assert(ft_simd_memchr(s, (char)0x80, sizeof s) == s + 4);
	assert(ft_simd_memchr(s, 'B', sizeof s) == NULL);
}

/*
 * Buffers placed against PROT_NONE guard pages: a read outside the mapped
 * area segfaults, so passing means no out-of-bounds page is touched.
 */
static void
test_page_boundaries(void)
{
	const size_t page = (size_t)sysconf(_SC_PAGESIZE);
	unsigned char *map = mmap(NULL, 3 * page, PROT_READ | PROT_WRITE,
	                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	assert(map != MAP_FAILED);
	assert(mprotect(map, page, PROT_NONE) == 0);
	assert(mprotect(map + 2 * page, page, PROT_NONE) == 0);

	unsigned char *mid = map + page;
	memset(mid, 'x', page);

	for (size_t n = 0; n <= 64; ++n) {
		/* buffer ends exactly at the end of the page */
		unsigned char *end = mid + page - n;
		assert(ft_simd_memchr(end, 'A', n) == NULL);
		if (n > 0) {
			end[n - 1] = 'A';
			assert(ft_simd_memchr(end, 'A', n) == end + n - 1);
			end[n - 1] = 'x';
		}

		/* buffer starts exactly at the start of the page */
		assert(ft_simd_memchr(mid, 'A', n) == NULL);
		if (n > 0) {
			mid[0] = 'A';
			assert(ft_simd_memchr(mid, 'A', n) == mid);
			mid[0] = 'x';
		}
	}

	/* whole page, match in the last byte */
	mid[page - 1] = 'A';
	assert(ft_simd_memchr(mid, 'A', page) == mid + page - 1);
	assert(ft_simd_memchr(mid + 3, 'A', page - 3) == mid + page - 1);

	/* n = SIZE_MAX must not overflow internally; stops at the match */
	assert(ft_simd_memchr(mid + 5, 'A', SIZE_MAX) == mid + page - 1);

	munmap(map, 3 * page);
}

void
test_simd_memchr(void)
{
	test_exhaustive();
	test_char_conversion();
	test_page_boundaries();
}
