#include "MemoryConsumer.hpp"
MemoryConsumer::MemoryConsumer(std::string name):MemoryAllocator(name){};
MemoryConsumer::~MemoryConsumer(){};
std::vector<Point> MemoryConsumer::getFromMemory(unsigned index){
    return buffer->buf[index].transferBufferToVector();
}