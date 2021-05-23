#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct lolo1 {
    int id;
    struct lolo1 *next, *prev;
};

struct lolo2 {
    int id;
    struct list_head _list; 
};

int main()
{
    // init
    // old linked-list
    struct lolo1 *list1 = (struct lolo1 *) malloc(sizeof(struct lolo1));
    list1->next = NULL;
    list1->prev = NULL;
    // new linked-list
    LIST_HEAD(list2);

    // adding 1 million entery
    int i, limit = 1000000;
    // list1
    struct lolo1 *iter = list1;
    for (i = 0; i < limit; i++) {
        struct lolo1 *entry1 = (struct lolo1 *) malloc(sizeof(struct lolo1));
        entry1->id = i;
        entry1->next = NULL;
        iter->next = entry1;
        iter = iter->next;
    }
    // list2
    for (i = 0; i < limit; i++) {
        struct lolo2 *entry2 = (struct lolo2 *) malloc(sizeof(struct lolo2));
        entry2->id = i;
        list_add_tail(&entry2->_list,&list2);
    }

	// old linked-list traverse and free time
	clock_t t;
    struct lolo1 *iter1, *iter_n1;
	t = clock();
    iter1 = list1->next;
    while (iter1) {
        iter_n1 = iter1->next;
        free(iter1);
        iter1 = iter_n1;
    }
    free(list1);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("old linked-list 1 million member traverse/free time: %f (seconds)\n", time_taken);
    
    // new linked-list traverse and free time
    struct lolo2 *iter2, *iter_n2;
	t = clock();
    list_for_each_entry_safe(iter2, iter_n2, &list2, _list) {
        free(iter2);
    }
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("new linked-list 1 million member traverse/free time: %f (seconds)\n", time_taken);

	return 0;
}
