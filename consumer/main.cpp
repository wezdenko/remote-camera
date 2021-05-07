#include "CommunicationStructs.hpp"
#include "FileSender.hpp"
#include "MemoryConsumer.hpp"
#include "QueReciver.hpp"
#include "SocketConnector.hpp"
#include "VectorSender.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <mqueue.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "FileDetector.hpp"
#include "FileSender.hpp"
#include "Def.h"


const char *QUEUE_NAME = "/test_queue";
const char *MEMORY_NAME = "/memory";


void draw(const std::vector<cv::Point2d> &points, cv::Mat &img) {
    const cv::Scalar imgColor(0, 0, 0);
    const cv::Scalar lineColor(0, 0, 255);

    const cv::Point2d *lastPoint = &points.front();

    for (const cv::Point2d &point : points) {
        cv::line(img, *lastPoint, point, lineColor);
        lastPoint = &point;
    }
}

int main() {

    auto isImage = [](std::string& name) -> bool{
        auto jpegLocation = name.find(".jpeg");
        if(jpegLocation>5 && jpegLocation<20){
            name = name.substr(2, jpegLocation-2);
            return true;
        }
        return false;
    };

    cv::Scalar backgroundColor(255, 255, 255); // white

    cv::Mat image(HEIGHT, WIDTH, CV_8UC3, backgroundColor);
    std::vector<uchar> imageVec;

    auto memory = MemoryConsumer(MEMORY_NAME);
    auto que = QueReciver(QUEUE_NAME, O_CREAT | O_RDONLY);
    auto socketConnector = SocketConnector(AF_INET, SOCK_STREAM);
    auto sendFunction = [&](std::string data) {
                    if (data.size() > 4)
                        socketConnector.sendData(data, 20);
                    else
                        socketConnector.sendData(data, 3);
    };
    while (true) {
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        draw(pointVec, image);
        if (!socketConnector.connectToServer(IP_ADDR, PORT)) {
            cv::imwrite("name.jpeg", image);
        } else {
            cv::imencode("name.jpeg", image, imageVec);
            auto vecSender = VectorSender<uchar>(imageVec);
            FileDetector fileDetector(".");
            auto files = fileDetector.getFilesName(isImage);
            if(files.size() > 1){
                auto fileSender = FileSender();
                for(const auto& file : files){
                    fileSender.transferFile(sendFunction, file);
                };
            }
            vecSender.transferFile(sendFunction, "name");
        }
    }
    return 0;
}