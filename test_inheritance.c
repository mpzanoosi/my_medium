#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

#define structinit(type, name) \
	type *name = (type *)malloc(sizeof(type))

#define structdup(obj) ({ \
    structinit(typeof(obj), obj_copy); \
	memcpy(obj_copy, obj, sizeof(typeof(obj))); })

struct person {
    char *name , *familyname, *fullname;
    char *eye_color;
    struct list_head children;
};

#define heritage \
    char *familyname; \
    char *eye_color;

struct child {
    heritage;
    char *gender;
    char *name;
    struct person *dad, *mom;
    struct list_head _list;
};

void test_inheritance()
{

}

struct person *new_person(char *name, char *familyname, char *eye_color)
{
    structinit(struct person, person_new);
    person_new->name = strdup(name);
    person_new->familyname = strdup(familyname);
    person_new->fullname = (char *)malloc((size_t)(strlen(name) + strlen(familyname) + 2));
    sprintf(person_new->fullname, "%s %s", name, familyname);
    person_new->eye_color = strdup(eye_color);
    INIT_LIST_HEAD(&person_new->children);
    return person_new;
}

struct child *new_child(struct person *dad, struct person *mom, char *gender, char *name)
{
    // making a new child
    // this is kind of having sex in programming, lol
    structinit(struct child, child_new);
    // applying inheritance:
    // inheritance is defined not only through its
    // pettern (children are made with two people,
    // mom and dad), but also should define which 
    // person objects should be used exactly (dad
    // and mom pointers)
    child_new->familyname = strdup(dad->familyname);
    child_new->eye_color = strdup(mom->eye_color);
    // giving specific parts
    child_new->gender = strdup(gender);
    child_new->name = strdup(name);

    // child_new should be added to the list of mom and dad children
    list_add_tail(&child_new->_list, &dad->children);
    list_add_tail(&child_new->_list, &mom->children);
    // setting mom and dad pointers
    child_new->mom = mom;
    child_new->dad = dad;

    return child_new;
}

void print_child(struct child *ch)
{
    printf("child information:\n");
    printf("\tname = '%s'\n", ch->name);
    printf("\tfamily name = '%s'\n", ch->familyname);
    printf("\tgender = '%s'\n", ch->gender);
    printf("\teye color = '%s'\n", ch->eye_color);
    printf("\tMom = '%s'\n", ch->mom->fullname);
    printf("\tDad = '%s'\n", ch->dad->fullname);
}

void test_multiinheritance()
{
    struct person *dad1 = new_person("Ross", "Geller", "dark");
    struct person *mom1 = new_person("Rachel", "Green", "blue");
    struct child *child1 = new_child(dad1, mom1, "girl", "Emma");
    print_child(child1);
}

int main()
{
    test_inheritance();
    test_multiinheritance();

    return 0;
}