#include <string>
#include <vector>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include "MemoryProducer.hpp"
#include "QueSender.hpp"
#include "Camera.hpp"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

int main(){
    auto memory = MemoryProducer(MEMORY_NAME);
    auto que = QueSender(QUEUE_NAME, O_WRONLY);
    int fps = 5;
    int numOfEdges = 10;
    int threshold = 230;
    int delay = fps * 3;
    double maxError = 0.1;

    Camera camera(numOfEdges, threshold, delay, maxError);

    while (true) {
        camera.processFrame();
        if(camera.isEndOfMovement()){
            memory.addToMemory(camera.movDetection.points);
        }
        que.sendData(std::to_string(memory.getCurrentIndex()));


        usleep((1000 / fps) * 1000);
    }
    return 0;
}