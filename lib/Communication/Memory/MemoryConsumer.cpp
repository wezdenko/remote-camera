#include "MemoryConsumer.hpp"
MemoryConsumer::MemoryConsumer(std::string name):MemoryAllocator(name){};
MemoryConsumer::~MemoryConsumer(){};
std::vector<Point> MemoryConsumer::getFromMemory(unsigned index){
    std::vector<Point> points;
    Point point;
    // Copying buffer elements
    for(int i=0; i<LIST_SIZE; i++){
        point = buffer->buf[index].buf[i];
        if(point.x != -1.0)
        points.push_back(Point(point));
    }
    return points;
}