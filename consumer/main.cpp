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

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"


const char* QUEUE_NAME =  "/test_queue";
const char* MEMORY_NAME = "/memory";


void draw(const std::vector<cv::Point2d> &points, cv::Mat &img) {
    const cv::Scalar imgColor(0, 0, 0);
    const cv::Scalar lineColor(0, 0, 255);

    const cv::Point2d *lastPoint = &points.front();

    for (const cv::Point2d &point : points) {
        cv::line(img, *lastPoint, point, lineColor);
        lastPoint = &point;
    }
}

int main(){
    int width = 640;
    int height = 480;
    cv::Scalar backgroundColor(255, 255, 255); // white

    cv::Mat image(height, width, CV_8UC3, backgroundColor);

    auto memory = MemoryConsumer(MEMORY_NAME);
    auto que = QueReciver(QUEUE_NAME, O_CREAT | O_RDONLY);
    while(true){
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        draw(pointVec, image);
        cv::imwrite("name.jpeg", image);
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