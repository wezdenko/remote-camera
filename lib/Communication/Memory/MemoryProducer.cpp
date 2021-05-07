#include "MemoryProducer.hpp"
MemoryProducer::MemoryProducer(std::string name):MemoryAllocator(name){};
MemoryProducer::~MemoryProducer(){};
int MemoryProducer::addToMemory(const std::vector<Point>& points){
    if(points.size() > LIST_SIZE) return -1;
    lastMemoryIndex = (lastMemoryIndex+1)%MEMORY_SIZE;
    // HERE IS THE IMPORTED GLOBAL CLASS
    MoveBuffer moveBuffer(points);
    buffer->buf[lastMemoryIndex] = moveBuffer;
    return lastMemoryIndex;
}
unsigned MemoryProducer::getCurrentIndex(){
    return lastMemoryIndex;
}