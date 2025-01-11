#pragma once
#include <iostream>
#include <unordered_map>
#include <mutex>

typedef std::unordered_map<void*, size_t> GarbageMemory;

class GarbageCollector {
    private:
    GarbageMemory memory;
    std::mutex GarbageMutex;
    public:
    template<typename T>
    T* allocate(){
        std::lock_guard<std::mutex> lock(this->GarbageMutex);
        T* ptr = static_cast<T*>(malloc(sizeof(T)));
        if (!ptr) { throw std::bad_alloc(); }
        new (ptr) T();
        this->memory[ptr] = sizeof(T);
        return ptr;
    };
    template<typename T>
    void deallocate(T* ptr){
        std::lock_guard<std::mutex> lock(this->GarbageMutex);
        if (this->memory.find(ptr) != this->memory.end()) {
            ptr->~T();
            free(ptr);
            this->memory.erase(ptr);
            ptr = nullptr;
        } else {
            std::cout << "Cannot find ptr!" << "\n";
        }
    };
    ~GarbageCollector() noexcept {
        std::lock_guard<std::mutex> lock(this->GarbageMutex);
        std::cout << "Releasing allocated memory." << "\n";
        for (auto& [ptr, size] : this->memory){
            free(ptr);
        }
        this->memory.clear();
        std::cout << "Memory released." << "\n";
    }
};