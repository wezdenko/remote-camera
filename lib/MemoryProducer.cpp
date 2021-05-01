#include "MemoryProducer.hpp"
MemoryProducer::MemoryProducer(std::string name=MEMORY_NAME):MemoryAllocator(name){};
MemoryProducer::~MemoryProducer(){};
unsigned MemoryProducer::addToMemory(std::vector<Point> points){
    lastMemoryIndex = (lastMemoryIndex+1)%BUFFER_LENGTH;
    if(points.size()>POINTS_NUMBER) return;
    for(int i=0;i<POINTS_NUMBER;i++){
        if(i<points.size()){
            buffer->buf[lastMemoryIndex][i] = points[i];
        }
        else buffer->buf[lastMemoryIndex][i] = Point(-1, -1);
    }
}
unsigned MemoryProducer::getCurrentIndex(){
    return lastMemoryIndex;
}