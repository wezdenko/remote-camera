#include "MemoryProducer.hpp"
MemoryProducer::MemoryProducer(std::string name):MemoryAllocator(name){};
MemoryProducer::~MemoryProducer(){};
unsigned MemoryProducer::addToMemory(const std::vector<Point>& points){
    lastMemoryIndex = (lastMemoryIndex+1)%MEMORY_SIZE;
    //if(points.size()>POINTS_NUMBER) return ERROR;
    for(int i=0;i<LIST_SIZE;i++){
        // TU WYPIERDALA PRZY 6 DODAWANIU
        if(i<points.size()){
            buffer->buf[lastMemoryIndex][i] = Point(points[i]);
        }
        // sygnalizacja że nie ma dobrych danych
        //else buffer->buf[lastMemoryIndex][i] = Point(-1, -1);
    }
    return lastMemoryIndex;
}
unsigned MemoryProducer::getCurrentIndex(){
    return lastMemoryIndex;
}