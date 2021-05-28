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

struct person {
    char *name, *firstname, *lastname;
    char *sex;
    char *eyecolor, *skincolor;
    struct person *mom, *dad;
    struct list_head children;
    
    struct list_head _list_dad;
    struct list_head _list_mom;

    struct list_head _list;
};

char *make_lastname(struct person *dad, struct person *mom)
{
    char *lastname = (char *)malloc((size_t)(strlen(dad->lastname) + strlen(mom->lastname) + 2));
    sprintf(lastname, "%s-%s", dad->lastname, mom->lastname);
    return lastname;
}

char *make_fullname(struct person *p)
{
    char *fullname = (char *)malloc((size_t)(strlen(p->firstname) + strlen(p->lastname) + 2));
    sprintf(fullname, "%s %s", p->firstname, p->lastname);
    return fullname;
}

struct person *new_person(char *firstname, char *lastname, char *sex, char *eyecolor, char *skincolor,
    struct person *dad, struct person *mom)
{
    // making a new person object
    structinit(struct person, person_new);
    INIT_LIST_HEAD(&person_new->_list_dad);
    INIT_LIST_HEAD(&person_new->_list_mom);
    // naming
    person_new->firstname = strdup(firstname);
    person_new->lastname = strdup(lastname);
    person_new->name = strdup(firstname);
    strcat(person_new->name, " ");
    strcat(person_new->name, lastname);
    // characteristics
    person_new->sex = strdup(sex);
    person_new->eyecolor = strdup(eyecolor);
    person_new->skincolor = strdup(skincolor);
    // internal pointers
    person_new->dad = dad;
    person_new->mom = mom;
    // children list
    INIT_LIST_HEAD(&person_new->children);
    // returning new pointer
    return person_new;
}

struct person *new_child(struct person *dad, struct person *mom,
    char *givenname, char *sex)
{
    // this is like programming sex somehow, lol
    // making a new child
    structinit(struct person, child_new);
    child_new->firstname = strdup(givenname);
    child_new->lastname = make_lastname(dad, mom);
    child_new->name = make_fullname(child_new);
    child_new->sex = strdup(sex);
    // this is where we *do* inheritance
    // inheritance pattern:
    //    - eyecolor is inherited from mom
    //    - skincolor is inherited from dad
    // inheritance:
    //    - child_new->eyecolor is filled with 'mom' object
    //    - child_new->skincolor is filled with 'dad' object
    // 
    // in this example inheritance pattern is "fixed":
    //    eyecolor is always inherited from mom and 
    //    skincolor is always inherited from dad
    // in this example inheritance is "flexible":
    //    each child_new object is going to be set up
    //    with different 'dad' and 'mom' objects
    child_new->eyecolor = strdup(mom->eyecolor);
    child_new->skincolor = strdup(dad->skincolor);
    // now filling mom/dad pointers for this children
    child_new->mom = mom;
    child_new->dad = dad;
    // adding new child into the children list of mom and dad
    list_add_tail(&child_new->_list_mom, &mom->children);
    list_add_tail(&child_new->_list_dad, &dad->children);
    INIT_LIST_HEAD(&child_new->children);

    return child_new;
}

struct person *new_child2(
    struct person *dad, int dad_heritage_offset,
    struct person *mom, int mom_heritage_offset,
    char *givenname, 
    char *sex)
{
    // this is like programming sex somehow, lol
    // making a new child
    structinit(struct person, child_new);
    child_new->firstname = strdup(givenname);
    child_new->lastname = make_lastname(dad, mom);
    child_new->name = make_fullname(child_new);
    child_new->sex = strdup(sex);
    // this is where we *do* inheritance
    // dad heritage
    char **source_addr_dad = (char **)((char *)dad + dad_heritage_offset);
    char **member_addr_dad = (char **)((char *)child_new + dad_heritage_offset);
    *member_addr_dad = strdup(*source_addr_dad);
    // mom heritage
    char **source_addr_mom = (char **)((char *)mom + mom_heritage_offset);
    char **member_addr_mom = (char **)((char *)child_new + mom_heritage_offset);
    *member_addr_mom = strdup(*source_addr_mom);
    // now filling mom/dad pointers for this children
    child_new->mom = mom;
    child_new->dad = dad;
    // adding new child into the children list of mom and dad
    list_add_tail(&child_new->_list_mom, &mom->children);
    list_add_tail(&child_new->_list_dad, &dad->children);
    INIT_LIST_HEAD(&child_new->children);

    return child_new;
}

void print_person_(struct person *p, int firstlineprint)
{
    if (firstlineprint) {
        printf("Informaion of %s:\n", p->firstname);
    }

    printf("\tname = %s\n", p->name);
    printf("\tsex = %s\n", p->sex);
    printf("\teyecolor = %s\n", p->eyecolor);
    printf("\tskincolor = %s\n", p->skincolor);
    // printing mom and dad
    if (p->mom) {
        printf("\tmom:\n");
        print_person_(p->mom, 0);
    }
    if (p->dad) {
        printf("\tdad:\n");
        print_person_(p->dad, 0);
    }
    // printing children
    if (!list_empty(&p->children)) {
        printf("\tchildren:");
        struct person *iter;
        if (!strcmp(p->sex, "female")) {
            list_for_each_entry(iter, &p->children, _list_mom) {
                printf(" %s ", iter->name);
            }
        } else {
            list_for_each_entry(iter, &p->children, _list_dad) {
                printf(" %s ", iter->name);
            }
        }
        printf("\n");
    }
}

void print_person(struct person* p)
{
    int firstlineprint = 1;
    print_person_(p, firstlineprint);
}

void destroy_person(struct person *p)
{
    free(p->firstname);
    free(p->lastname);
    free(p->name);
    free(p->sex);
    free(p->eyecolor);
    free(p->skincolor);
    list_del(&p->_list_dad);
    list_del(&p->_list_mom);
    free(p);
}

void test_inheritance()
{
    struct person *ross = new_person("Ross", "Geller", "male", "dark", "white", NULL, NULL);
    struct person *rachel = new_person("Rachel", "Green", "female", "blue", "brown", NULL, NULL);
    // struct person *emma = new_child(ross, rachel, "Emma", "female");
    int dad_heritage_offset = list_offsetof(struct person, skincolor);
    int mom_heritage_offset = list_offsetof(struct person, eyecolor);
    struct person *emma = new_child2(ross, dad_heritage_offset, rachel, mom_heritage_offset, "Emma", "female");
    // print_person(ross);
    // print_person(rachel);
    print_person(emma);

    // freeing memory
    destroy_person(rachel);
    destroy_person(ross);
    destroy_person(emma);
}

int main()
{
    test_inheritance();
    // test_multiinheritance();

    return 0;
}

