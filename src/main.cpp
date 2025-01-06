#include <iostream>
#include "garbage.hpp"

int main(void){
    GarbageCollector gc;
    int* ptr = (int*)gc.allocate(sizeof(int));
    *ptr = 45;
    std::cout << "Valor: " << *ptr << "\n";
    gc.deallocate(ptr);
    return EXIT_SUCCESS;
}