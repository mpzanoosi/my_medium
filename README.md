# list.h
Linux kernel doubly linked-list example codes relating to my medium post\
[Why Linux kernel doubly linked-list is not just a simple linked-list?!](https://medium.com/@m.zanoosi/why-linux-kernel-doubly-linked-list-is-not-just-a-simple-linked-list-fb8c43ff150)\
and\
[Inheritance in C; not a new feature but a new way of looking!](https://medium.com/@m.zanoosi/inheritance-in-c-not-a-new-feature-but-a-new-way-of-looking-5cfc117cb67c)

`test_timing.c`: program to compare timing of old-style and new-style linked-list implementations\
`test_nested_list.c`: program to implement and test nested linked list concept\
`test_polymorphism.c`: program to implement and test true polymorphism in C ([see my medium post](https://medium.com/@m.zanoosi/why-linux-kernel-doubly-linked-list-is-not-just-a-simple-linked-list-fb8c43ff150))\
`test_inhertiance.c` and `test_inheritance_2.c`: programs to implement and test inheritance in C ([see my medium post](https://medium.com/@m.zanoosi/inheritance-in-c-not-a-new-feature-but-a-new-way-of-looking-5cfc117cb67c))

# build and test run
```
mkdir build
cd build
cmake ..
make
# for instance
./tests/test_polymorphism
# valgrind memory check (need valgrind installation)
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tests/test_polymorphism
```

---
**NOTE**

`test_inheritance.c` has not been developed completely

---
