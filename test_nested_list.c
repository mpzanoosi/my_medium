#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

// program to test a nested linked-list in another linked-list object

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
    struct list_head children;
    struct list_head _list; 
};

int main()
{
    // making a parent object
    printf("making perent object of type: 'struct parent'\n");
    structinit(struct parent, parent_obj);
    INIT_LIST_HEAD(&parent_obj->children);
    // making some children
    printf("making two children objects of type: 'struct child'\n");
    structinit(struct child, child_1);
    structinit(struct child, child_2);
    // adding children into the internal list of the parnet
    list_add_tail(&child_1->_list, &parent_obj->children);
    list_add_tail(&child_2->_list, &parent_obj->children);
    printf("adding children into parent_obj->children\n");
    printf("now you can traverse children of parent_obj\n");
    printf("\tand each parent object has its own children list\n");

    // freeing
    printf("freeing all things up\n");
    struct child *iter, *iter_n;
    list_for_each_entry_safe(iter, iter_n, &parent_obj->children, _list) {
        free(iter);
    }
    
    free(parent_obj);

	return 0;
}
