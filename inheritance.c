#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct parent {
    int id;
    struct list_head _list; 
};

struct child {
    struct parent _parent;
    char *name;
    struct list_head _list;
};


// The main program calls fun1() and measures time taken by fun1()
int main()
{
    LIST_HEAD(children);
    // making a child
    structinit(struct child, child1);
    child1->_parent.id = 1;
    // adding children
    list_add_tail(&child1->_list, &children);

	return 0;
}
