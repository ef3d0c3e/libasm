#include <libasm.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int
cmp_int(const void *a, const void *b)
{
	const int x = *(const int *)a;
	const int y = *(const int *)b;
	return (x > y) - (x < y);
}

static int
cmp_str(const void *a, const void *b)
{
	return ft_strcmp(a, b);
}

static t_list *
from_array(int *vals, size_t n)
{
	t_list *list = NULL;
	for (size_t i = n; i-- > 0;)
		ft_list_push_front(&list, &vals[i]);
	return list;
}

static void
free_list(t_list *l)
{
	while (l) {
		t_list *next = l->next;
		free(l);
		l = next;
	}
}

/* sorts `vals` through a list, checks against qsort */
static void
check_ints(const int *input, size_t n)
{
	int *vals = malloc(n * sizeof *vals);
	int *ref = malloc(n * sizeof *ref);
	memcpy(vals, input, n * sizeof *vals);
	memcpy(ref, input, n * sizeof *ref);
	qsort(ref, n, sizeof *ref, cmp_int);

	t_list *list = from_array(vals, n);
	ft_list_sort(&list, cmp_int);

	size_t i = 0;
	for (t_list *it = list; it; it = it->next, ++i)
		assert(*(int *)it->data == ref[i]);
	assert(i == n);

	free_list(list);
	free(vals);
	free(ref);
}

void
test_list_sort(void)
{
	/* NULL begin_list and empty list must not crash */
	ft_list_sort(NULL, cmp_int);
	t_list *empty = NULL;
	ft_list_sort(&empty, cmp_int);
	assert(empty == NULL);

	check_ints((int[]){ 42 }, 1);
	check_ints((int[]){ 2, 1 }, 2);
	check_ints((int[]){ 1, 2, 3, 4, 5 }, 5);
	check_ints((int[]){ 5, 4, 3, 2, 1 }, 5);
	check_ints((int[]){ 3, 1, 3, 2, 1, 3 }, 6);
	check_ints((int[]){ 0, -1, 2147483647, -2147483647 - 1, 7 }, 5);

	enum { N = 500 };
	int big[N];
	srand(42);
	for (int i = 0; i < N; ++i)
		big[i] = rand() % 100 - 50;
	check_ints(big, N);

	/* strings, compared with ft_strcmp */
	char *words[] = { "pear", "apple", "fig", "banana", "apple", "" };
	const char *sorted[] = { "", "apple", "apple", "banana", "fig", "pear" };
	t_list *list = NULL;
	for (size_t i = 0; i < sizeof words / sizeof *words; ++i)
		ft_list_push_front(&list, words[i]);
	ft_list_sort(&list, cmp_str);
	size_t i = 0;
	for (t_list *it = list; it; it = it->next, ++i)
		assert(strcmp(it->data, sorted[i]) == 0);
	assert(i == sizeof sorted / sizeof *sorted);
	free_list(list);
}
