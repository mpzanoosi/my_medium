# list.h
Linux kernel doubly linked-list example codes relating to my medium post\
[Why Linux kernel doubly linked-list is not just a simple linked-list?!](https://medium.com/@m.zanoosi/why-linux-kernel-doubly-linked-list-is-not-just-a-simple-linked-list-fb8c43ff150)

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
