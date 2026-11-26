#include <libasm.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

static void
free_list(t_list *l)
{
	while (l) {
		t_list *next = l->next;
		free(l);
		l = next;
	}
}

void
test_list_push_front(void)
{
	int a = 1, b = 2, c = 3;

	/* push onto an empty list */
	t_list *list = NULL;
	ft_list_push_front(&list, &a);
	assert(list != NULL);
	assert(list->data == &a);
	assert(list->next == NULL);

	/* subsequent pushes go to the front, older nodes are kept */
	t_list *first = list;
	ft_list_push_front(&list, &b);
	assert(list != first);
	assert(list->data == &b);
	assert(list->next == first);

	ft_list_push_front(&list, &c);
	assert(list->data == &c);
	assert(list->next->data == &b);
	assert(list->next->next->data == &a);
	assert(list->next->next->next == NULL);

	/* NULL data is a valid payload */
	ft_list_push_front(&list, NULL);
	assert(list->data == NULL);
	assert(list->next->data == &c);

	free_list(list);

	/* many pushes: order is reversed, length matches */
	enum { N = 1000 };
	static int vals[N];
	list = NULL;
	for (int i = 0; i < N; ++i) {
		vals[i] = i;
		ft_list_push_front(&list, &vals[i]);
	}
	int expected = N - 1;
	for (t_list *it = list; it; it = it->next)
		assert(*(int *)it->data == expected--);
	assert(expected == -1);

	free_list(list);
}
