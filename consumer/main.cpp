#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <mqueue.h>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "Communication/CommunicationStructs.hpp"
#include "FileLib/FileSender.hpp"
#include "Communication/Memory/MemoryConsumer.hpp"
#include "Communication/Queue/QueReceiver.hpp"
#include "Socket/SocketConnector.hpp"
#include "FileLib/VectorSender.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "FileLib/FileDetector.hpp"
#include "FileLib/FileSender.hpp"
#include "FileLib/Date.hpp"
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
    auto que = QueReceiver(QUEUE_NAME, O_CREAT | O_RDONLY);
    auto socketConnector = SocketConnector(AF_INET, SOCK_STREAM);
    auto sendFunction = [&](std::string data) {
                    if (data.size() > DATA_SIZE)
                        socketConnector.sendData(data, FILE_NAME_SIZE);
                    else
                        socketConnector.sendData(data, DATA_SIZE);
    };
    while (true) {
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        draw(pointVec, image);
        auto date = Date::getTime();
        if (!socketConnector.connectToServer(IP_ADDR, PORT)) {
            cv::imwrite(date+".jpeg", image);
        } else {
            cv::imencode(date+".jpeg", image, imageVec);
            auto vecSender = VectorSender<uchar>(imageVec);
            FileDetector fileDetector(".");
            auto files = fileDetector.getFilesName(isImage);
            if(files.size() > 1){
                auto fileSender = FileSender();
                for(const auto& file : files){
                    fileSender.transferFile(sendFunction, file);
                };
            }
            vecSender.transferFile(sendFunction, date);
        }
    }
    return 0;
}