#include <iostream>
#include <string>
#include <garbage.hpp>

int main(void){
    GarbageCollector gc;
    int* a = (int*)gc.allocate<int>();

    std::cout << a << "\n";
    gc.deallocate<int>(a);

    return EXIT_SUCCESS;
}