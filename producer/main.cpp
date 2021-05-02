#include <string>
#include <vector>
#include <mqueue.h>
#include <stdio.h>
#include "MemoryProducer.hpp"
#include "QueSender.hpp"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

int main(){
    auto memory = MemoryProducer(MEMORY_NAME);
    auto que = QueSender(QUEUE_NAME, O_WRONLY);
    std::vector<Point> data;
    for(int i=0; i<250;i++)
        data.push_back(Point(6.9,6.9));
    int memoryIndex;
    while(true){
        if((memoryIndex = memory.addToMemory(data))==-1)
        {
            return -1;
        }
        que.sendData(std::to_string(memoryIndex));
        sleep(0.5);
    }
    return 0;
}