#pragma once
#include "MemoryAllocator.hpp"
#include <vector>

class MemoryConsumer : public MemoryAllocator {
  public:
    MemoryConsumer(std::string name);
    std::vector<Point> getFromMemory(unsigned index);
    virtual ~MemoryConsumer();
};