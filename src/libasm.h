#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <unistd.h>

#ifndef __x86_64__
#error Only x86_64 is supported
#endif

size_t
ft_strlen(const char* s);
size_t
ft_strcpy(char* restrict dst, const char* restrict src);
int
ft_strcmp(const char* s1, const char* s2);
char*
ft_strdup(const char* s);
void*
ft_calloc(size_t nmemb, size_t size);

ssize_t
ft_write(int fd, const void* buf, size_t count);
ssize_t
ft_read(int fd, const void* buf, size_t count);

int
ft_atoi_base(const char* str, const char* base);

typedef struct s_list
{
	void* data;
	struct s_list* next;
} t_list;

void
ft_list_push_front(t_list** begin_list, void* data);
unsigned int
ft_list_size(const t_list* begin_list);
void
ft_list_sort(t_list** begin_list, int (*cmp)(void));

void*
ft_simd_memchr(const void* s, int c, size_t n);

#endif // LIBASM_H
