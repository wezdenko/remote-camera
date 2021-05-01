#include "MemoryConsumer.hpp"
MemoryConsumer::MemoryConsumer(std::string name=MEMORY_NAME):MemoryAllocator(name){};
MemoryConsumer::~MemoryConsumer(){};
std::vector<Point> MemoryConsumer::getFromMemory(unsigned index){
    std::vector<Point> points;
    for(int i=0; i<POINTS_NUMBER; i++){
        auto point = buffer->buf[index][i];
        if(point.xPos != -1 && point.yPos != -1){
            points.push_back(point);
        }
    }
}