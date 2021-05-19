#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct child {
    char *name;
    struct list_head _list;
};

struct parent {
    int id;
    struct list_head internal_list_head;
    struct list_head _list; 
};


// The main program calls fun1() and measures time taken by fun1()
int main()
{
    // making a parent object
    structinit(struct parent, parent_obj);
    INIT_LIST_HEAD(&parent_obj->internal_list_head);
    // making some children
    structinit(struct child, child_1);
    structinit(struct child, child_2);
    // adding children into the internal list of the parnet
    list_add_tail(&child_1->_list, &parent_obj->internal_list_head);
    list_add_tail(&child_2->_list, &parent_obj->internal_list_head);

	return 0;
}
