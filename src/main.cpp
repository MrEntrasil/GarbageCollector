#include <iostream>
#include <string>
#include <garbage.hpp>

int main(void){
    GarbageCollector gc;
    std::string* ptr = (std::string*)gc.allocate(sizeof(int));
    *ptr = "asasas";
    std::cout << "Valor: " << *ptr << "\n";
    return EXIT_SUCCESS;
}