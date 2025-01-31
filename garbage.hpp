#pragma once
#include <iostream>
#include <unordered_map>
#include <mutex>

typedef std::unordered_map<void*, size_t> GarbageMemory;

class GarbageCollector {
    private:
    GarbageMemory memory;
    std::mutex garbageMutex;
    public:
    void* allocate(size_t size){
        if (!size) { throw std::bad_alloc(); }
        std::lock_guard<std::mutex> lock(this->garbageMutex);
        void* ptr = malloc(size);
        this->memory[ptr] = size;

        return ptr;
    }
    void deallocate(void* obj) {
        if (!obj) { throw std::bad_alloc(); }
        std::lock_guard<std::mutex> lock(this->garbageMutex);

        if (this->memory.find(obj) != this->memory.end()) {
            free(obj);
            this->memory.erase(obj);
        } else {
            printf("Could not find pointer...\n");
        }
    }
    ~GarbageCollector() noexcept {
        std::lock_guard<std::mutex> lock(this->garbageMutex);

        printf("Releasing allocated memory.\n");
        for (auto& [ptr, size] : this->memory) {
            free(ptr);
        }

        this->memory.clear();
        printf("Memory released.\n");
    }
};