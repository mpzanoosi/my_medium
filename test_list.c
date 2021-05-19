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

// The main program calls fun1() and measures time taken by fun1()
int main()
{
    // old linked-list
    // init
    struct lolo1 *list1 = (struct lolo1 *) malloc(sizeof(struct lolo1));
    list1->next = NULL;
    list1->prev = NULL;
    // add members
    struct lolo1 *head = list1;
    int i, limit = 10;
    for (i = 0; i < limit; i++) {
        structinit(struct lolo1, new_entry);
        new_entry->id = i;
        new_entry->next = NULL;
        new_entry->prev = head;
        head->next = new_entry;
        head = new_entry;
    }
    // traverse
    struct lolo1 *iter1 = list1->next;
    while (iter1) {
        printf("member number %d\n", iter1->id);
        iter1 = iter1->next;
    }
    // safe free
    struct lolo1 *iter1_n;
    iter1 = list1->next;
    while (iter1) {
        iter1_n = iter1->next;
        free(iter1);
        iter1 = iter1_n;
    }
    free(list1);

    // new fashion linked-list
    // init
    LIST_HEAD(list2);
    // add members
    int j;
    for (j = 0; j < limit; j++) {
        structinit(struct lolo2, new_entry);
        new_entry->id = 10*j;
        list_add_tail(&new_entry->_list, &list2);
    }
    // traverse
    struct lolo2 *iter2;
    list_for_each_entry(iter2, &list2, _list) {
        printf("member number %d\n", iter2->id);
    }
    // safe free
    struct lolo2 *iter2_n;
    list_for_each_entry_safe(iter2, iter2_n, &list2, _list) {
        free(iter2);
    }



    // // init


    // LIST_HEAD(list2);
    // // adding 1 million entery
    // int i, limit = 1000000*10;
    // // list1
    // struct lolo1 *iter = list1;
    // for (i = 0; i < limit; i++) {
    //     struct lolo1 *entry1 = (struct lolo1 *) malloc(sizeof(struct lolo1));
    //     entry1->id = i;
    //     entry1->next = NULL;
    //     iter->next = entry1;
    //     iter = iter->next;
    // }
    // // list2
    // for (i = 0; i < limit; i++) {
    //     struct lolo2 *entry2 = (struct lolo2 *) malloc(sizeof(struct lolo2));
    //     entry2->id = i;
    //     list_add_tail(&entry2->_list,&list2);
    // }

	// // old linked-list traverse time
	// clock_t t;
    // struct lolo1 *iter1, *iter_n1;
	// t = clock();
    // iter1 = list1->next;
    // while (iter1) {
    //     iter_n1 = iter1->next;
    //     free(iter1);
    //     iter1 = iter_n1;
    // }
    // free(list1);
	// t = clock() - t;
	// double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	// printf("old took %f seconds to execute \n", time_taken);
    
    // // new linked-list traverse time
    // struct lolo2 *iter2, *iter_n2;
	// t = clock();
    // list_for_each_entry_safe(iter2, iter_n2, &list2, _list) {
    //     free(iter2);
    // }
	// t = clock() - t;
	// time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	// printf("new took %f seconds to execute \n", time_taken);

	return 0;
}
