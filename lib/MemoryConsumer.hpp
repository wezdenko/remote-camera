#pragma once
#include <vector>
#include "MemoryAllocator.hpp"

class MemoryConsumer: public MemoryAllocator{
    public:
        MemoryConsumer(std::string name);
        std::vector<Point> getFromMemory(unsigned index);
        virtual ~MemoryConsumer();
};