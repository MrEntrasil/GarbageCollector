# GarbageCollector
Yeah my own garbage collector

example
```cpp
#include <iostream>
#include <garbage.hpp>

int main(void){
    GarbageCollector gc;
    int* a = (int*)gc.allocate(sizeof(int*));
    *a = 54;
    printf("%d\n", *a);
    gc.deallocate(a);

    return 0;
}
```