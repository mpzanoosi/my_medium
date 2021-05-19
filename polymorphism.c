#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct shape {
    struct list_head _list;
    int id;
    double area;
};

#define  shape_heritage  \
    struct list_head _list; \
    struct shape _shape; 

struct shape_spirit {
    shape_heritage;
};


struct square {
    shape_heritage;
    double edge;
};

struct rectangular {
    shape_heritage;
    double length, width;
};

struct square *new_square(int id, double edge)
{
    structinit(struct square, square1);
    square1->_shape.id = id;
    square1->edge = edge;
    square1->_shape.area = edge * edge;
    return square1;
}

struct rectangular *new_rect(int id, double width, double length)
{
    structinit(struct rectangular, rect1);
    rect1->_shape.id = id;
    rect1->width = width;
    rect1->length = length;
    rect1->_shape.area = width * length;;
    return rect1;
}

void shape_printArea(struct shape *this)
{
    struct shape_spirit *temp = (struct shape_spirit *)this;
    printf("area = %f\n", temp->_shape.area);
}

void func();

int main()
{
    func();
    // LIST_HEAD(shape_list);
    // // making a square and a rectangular
    // struct square *square1 = new_square(1, 10.5);
    // struct rectangular *rect1 = new_rect(2, 2.76, 5.5);
    // // adding all objects into a unified list (this is the magic)
    // list_add_tail(&square1->_list, &shape_list);
    // list_add_tail(&rect1->_list, &shape_list);
    
    // // now let's traverse the list
    // struct shape *iter;
    // list_for_each_entry(iter, &shape_list, _list) {
    //     shape_printArea(iter);
    // }

	return 0;
}

void func()
{
    // making shape_list
    LIST_HEAD(shape_list);
    
    // making a square
    structinit(struct square, square1);
    square1->_shape.id = 1;
    square1->edge = 10.5;
    // making a rectangular
    structinit(struct rectangular, rectangular1);
    rectangular1->_shape.id = 2;
    rectangular1->length = 2.76;
    rectangular1->width = 5.5;
    
    // filling shape_list
    list_add_tail(&square1->_list, &shape_list);
    list_add_tail(&rectangular1->_list, &shape_list);

    // traversing and printing area (polymorphism)
    struct shape *iter;
    list_for_each_entry(iter, &shape_list, _list) {
        printf("----- id = %d\n", iter->id);
    }
}