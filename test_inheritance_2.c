#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct shape {
    double area;
};

#define shape_heritage \
    int id; \
    double area;

struct square {
    shape_heritage;
    double edge;
};

#define square_heritage \
    shape_heritage; \
    double edge;

struct square_colorful {
    square_heritage;
    char *color;
};

struct color {
    char *color;
};

#define heritage \
    double area; \
    char *color;

struct square_colorful_2 {
    heritage;
    double edge;
};

struct square *new_square(double edge)
{
    structinit(struct square, square_new);
    square_new->edge = edge;
    square_new->area = edge * edge;
    return square_new;
}

struct square_colorful *new_square_colorful(double edge, char *color)
{
    structinit(struct square_colorful, square_new);
    square_new->edge = edge;
    square_new->area = edge * edge;
    square_new->id = 0;
    square_new->color = strdup(color);
    return square_new;
}

void test_inheritance_2()
{
    printf("test_inheritance_2...\n");
    struct square *square1 = new_square(10.25);
    printf("square 1 area = %f\n", square1->area);
    free(square1);
    printf("\n");
}

void test_inheritance_2_deep()
{
    printf("test_inheritance_2_deep...\n");
    struct square_colorful *square2 = new_square_colorful(3.4, "grey");
    printf("square 2 id = %d\n", square2->id);
    printf("square 2 area = %f\n", square2->area);
    printf("square 2 color = %s\n", square2->color);
    free(square2->color);
    free(square2);
    printf("\n");
}

void test_inheritance_2_multi()
{
    printf("test_inheritance_2_multi...\n");
    structinit(struct square_colorful_2, square3);
    square3->edge = 3.14;
    square3->area = 3.14 * 3.14;
    square3->color = "blue";
    printf("square 3 edge = %f\n", square3->edge);
    printf("square 3 area = %f\n", square3->area);
    printf("square 3 color = %s\n", square3->color);
    free(square3);
    printf("\n");
}

int main()
{
    test_inheritance_2();
    test_inheritance_2_deep();
    test_inheritance_2_multi();

    return 0;
}