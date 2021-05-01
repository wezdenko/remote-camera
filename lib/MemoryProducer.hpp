#pragma once
#include <vector>
#include "MemoryAllocator.hpp"

class MemoryProducer: public MemoryAllocator{
    public:
        MemoryProducer(std::string name);
        unsigned addToMemory(std::vector<Point> points);
        unsigned getCurrentIndex();
        virtual ~MemoryProducer();
    private:
        unsigned lastMemoryIndex=0;
};