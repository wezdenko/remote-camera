#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <mqueue.h>
#include <unistd.h>
#include "CommunicationStructs.hpp"
#include "MemoryConsumer.hpp"
#include "QueReciver.hpp"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

int main(){
    auto memory = MemoryConsumer(MEMORY_NAME);
    auto que = QueReciver(QUEUE_NAME, O_CREAT | O_RDONLY);
    while(true){
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        unsigned number = 0;
        std::cout<<"INDEX: "<<index<<std::endl;
        for(auto& point: pointVec){
            if (point.x > 0 || point.y > 0) {
                std::cout<<number;
                std::cout<<" Point x: "<<point.x<<" Point y: "<<point.y<<std::endl;
            }
            number++;
        }
    }
    return 0;
}