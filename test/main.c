#include <stdio.h>

void test_strlen(void);
void test_strcpy(void);
void test_strcmp(void);
void test_write(void);
void test_read(void);
void test_strdup(void);
void test_calloc(void);
void test_atoi_base(void);
void test_list_push_front(void);

#define run(x) do { printf("%s... ", #x); test_ ## x(); printf("OK\n"); } while (0)

int main(void)
{
	run(strlen);
	run(strcpy);
	run(strcmp);
	run(write);
	run(read);
	run(strdup);
	run(calloc);
	run(atoi_base);
	run(list_push_front);
}
