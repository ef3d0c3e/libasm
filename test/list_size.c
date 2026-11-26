#include <libasm.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

void
test_list_size(void)
{
	/* empty list */
	assert(ft_list_size(NULL) == 0);

	/* hand-built lists, independent of ft_list_push_front */
	t_list n3 = { .data = NULL, .next = NULL };
	t_list n2 = { .data = NULL, .next = &n3 };
	t_list n1 = { .data = NULL, .next = &n2 };
	assert(ft_list_size(&n3) == 1);
	assert(ft_list_size(&n2) == 2);
	assert(ft_list_size(&n1) == 3);

	/* larger list built with ft_list_push_front */
	enum { N = 1000 };
	t_list *list = NULL;
	for (unsigned int i = 1; i <= N; ++i) {
		ft_list_push_front(&list, NULL);
		assert(ft_list_size(list) == i);
	}

	while (list) {
		t_list *next = list->next;
		free(list);
		list = next;
	}
}
