#include "MemoryConsumer.hpp"
MemoryConsumer::MemoryConsumer(std::string name):MemoryAllocator(name){};
MemoryConsumer::~MemoryConsumer(){};
std::vector<Point> MemoryConsumer::getFromMemory(unsigned index){
    std::vector<Point> points;
    for(int i=0; i<LIST_SIZE; i++){
        auto point = buffer->buf[index][i];
        points.push_back(point);
    }
    return points;
}