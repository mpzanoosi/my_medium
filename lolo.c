#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define structdup(obj) ({ \
	typeof(obj) *obj_copy = (typeof(obj) *)malloc(sizeof(typeof(obj))); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct lolo_new
{
	int id;
	char *name;
	struct list_head _list;
};

int main()
{
	LIST_HEAD(list1);
	LIST_HEAD(list2);

	struct lolo_new *entry1 = (struct lolo_new *)malloc(sizeof(struct lolo_new));
	entry1->id = 6;
	
	struct lolo_new *entry2 = structdup(entry1);

	list_add_tail(&entry1->_list, &list1);
	list_add_tail(&entry2->_list, &list2);

	struct lolo_new *iter;
	list_for_each_entry(iter, &list1, _list) {
		printf("list 1---> id = %d\n", iter->id);
	}
	list_for_each_entry(iter, &list2, _list) {
		printf("list 2---> id = %d\n", iter->id);
	}

	free(entry1);
	free(entry2);

	return 0;
}