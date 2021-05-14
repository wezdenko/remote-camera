#include <string>
#include <vector>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include "Communication/Memory/MemoryProducer.hpp"
#include "Communication/Queue/QueSender.hpp"
#include "Camera/Camera.hpp"
#include "Def.h"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

int main(){
    auto memory = MemoryProducer(MEMORY_NAME);
    auto que = QueSender(QUEUE_NAME, O_WRONLY);

    Camera camera(NUM_OF_EDGES, THRESHOLD, DELAY, MAX_ERROR);

    while (true) {
        camera.processFrame();
        if(camera.isEndOfMovement()){
            memory.addToMemory(camera.getPoints());
            que.sendData(std::to_string(memory.getCurrentIndex()));
            camera.clearPoints();
        }


        usleep((1000 / FPS) * 1000);
    }
    return 0;
}