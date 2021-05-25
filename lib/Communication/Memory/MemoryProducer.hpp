#pragma once
#include "MemoryAllocator.hpp"
#include <vector>

class MemoryProducer : public MemoryAllocator {
  public:
    MemoryProducer(std::string name);
    int addToMemory(const std::vector<Point> &points);
    unsigned getCurrentIndex();
    virtual ~MemoryProducer();

  private:
    unsigned lastMemoryIndex = 0;
};