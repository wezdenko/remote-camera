#include <string>
#include <vector>
#include <mqueue.h>
#include <stdio.h>
#include <sys/timerfd.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sched.h>
#include <unistd.h>
#include <algorithm>
#include "Communication/Memory/MemoryProducer.hpp"
#include "Communication/Queue/QueSender.hpp"
#include "Camera/Camera.hpp"
#include "Def.h"
#include <iostream>



const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";

void detectMovement(Camera& camera, MemoryProducer& memory, QueSender& que);


int main(){
    const sched_param* param;
    int result = sched_setscheduler(0, SCHED_FIFO, param);

    struct itimerspec timerValue;
    timerValue.it_value.tv_sec = 0;
    timerValue.it_value.tv_nsec = FREQUENCY;
    timerValue.it_interval.tv_sec = 0;
    timerValue.it_interval.tv_nsec = FREQUENCY;

    struct epoll_event epollEvent;

    int timerfd = timerfd_create(CLOCK_REALTIME, 0);
    timerfd_settime(timerfd, 0, &timerValue, NULL);

    epollEvent.events = EPOLLIN;
    epollEvent.data.fd = timerfd;

    auto memory = MemoryProducer(MEMORY_NAME);
    auto que = QueSender(QUEUE_NAME, O_WRONLY);

    Camera camera(NUM_OF_EDGES, THRESHOLD, DELAY, MAX_ERROR);

    int timersElapsed = 0;
    while (true) {
        auto info = read(epollEvent.data.fd, &timersElapsed, 64);
        detectMovement(camera, memory, que);
    }
    return 0;
}

void detectMovement(Camera& camera, MemoryProducer& memory, QueSender& que){
    camera.processFrame();
    if(camera.isEndOfMovement()){
        memory.addToMemory(camera.getPoints());
        que.sendData(std::to_string(memory.getCurrentIndex()));
        camera.clearPoints();
    }
}