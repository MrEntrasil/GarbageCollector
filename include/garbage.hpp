#pragma once
#include <iostream>
#include <unordered_map>

typedef std::unordered_map<void*, size_t> GarbageMemory;

class GarbageCollector {
    private:
    GarbageMemory memory;
    public:
    void* allocate(size_t size){
        void* ptr = malloc(size);
        this->memory[ptr] = size;
        return ptr;
    };
    void deallocate(void* ptr){
        if (this->memory.find(ptr) != this->memory.end()) {
            free(ptr);
            this->memory.erase(ptr);
        }
    };
    ~GarbageCollector(){
        std::cout << "Releasing allocated memory." << "\n";
        for (auto& [ptr, size] : this->memory){
            free(ptr);
        }
        this->memory.clear();
        std::cout << "Memory released.";
    }
};