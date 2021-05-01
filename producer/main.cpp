#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <mqueue.h>
#include <unistd.h>
#include "MemoryProducer.hpp"
#include "QueSender.hpp"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

int main(){
    std::cout<<"PRODUCTION STARTED!\n";
    auto memory = MemoryProducer(MEMORY_NAME);
    auto que = QueSender(QUEUE_NAME, O_WRONLY);
    unsigned x = 250;
    std::vector<Point> data;
    while(x>0){
        data.push_back(Point(6.9,6.9));
        x--;
    }
    unsigned memoryIndex = memory.addToMemory(data);
    que.sendData(std::to_string(memoryIndex));
    std::cout<<"PRODUCTION ENDED\n";
    // while(x<20){
    //     unsigned memoryIndex = memory.addToMemory(data);
    //     std::cout<<"HERE";
    //     que.sendData(std::to_string(memoryIndex));
    //     x++;
    //     sleep(2);
    // }

    return 0;
}