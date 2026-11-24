#define _GNU_SOURCE
#include <libasm.h>

#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define test(buf)                                                                                \
	do {                                                                                         \
		char name[256];                                                                          \
		sprintf(name, "write-test-%d", __COUNTER__);                                             \
		int fd = memfd_create(name, MFD_CLOEXEC);                                                \
		assert(fd != -1);                                                                        \
                                                                                                 \
		const size_t buflen = strlen(buf);                                                       \
		size_t nwritten = 0;                                                                     \
		while (nwritten < buflen) {                                                              \
			const ssize_t n = ft_write(fd, buf, buflen);                                         \
			if (n == -1 && errno != EINTR) {                                                     \
				perror("ft_write");                                                              \
				exit(1);                                                                         \
			}                                                                                    \
			nwritten += (size_t)n;                                                               \
		}                                                                                        \
                                                                                                 \
		off_t pos = lseek(fd, 0, SEEK_CUR);                                                      \
		assert(pos == (off_t)buflen);                                                            \
		lseek(fd, 0, SEEK_SET);                                                                  \
                                                                                                 \
		char* input = malloc(buflen + 1);                                                        \
		size_t nread = 0;                                                                        \
		while (nread < buflen) {                                                                 \
			const ssize_t n = read(fd, input + nread, buflen - nread);                           \
			if (n == -1 && errno != EINTR) {                                                     \
				perror("read");                                                                  \
				exit(1);                                                                         \
			}                                                                                    \
			nread += (size_t)n;                                                                  \
		}                                                                                        \
		close(fd);                                                                               \
                                                                                                 \
		assert(memcmp(buf, input, buflen) == 0);                                                 \
                                                                                                 \
		free(input);                                                                             \
	} while (0)

void
test_write(void)
{
	test("");
	test("abcdef");
	test("a");
	test("lorem ipsum dolor sit amet");
	test("\001\002\003");
}
