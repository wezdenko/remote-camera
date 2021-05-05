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
    int width = 640;
    int height = 480;
    cv::Scalar backgroundColor(255, 255, 255); // white

    cv::Mat image(height, width, CV_8UC3, backgroundColor);
    std::vector<uchar> imageVec;

    auto memory = MemoryConsumer(MEMORY_NAME);
    auto que = QueReciver(QUEUE_NAME, O_CREAT | O_RDONLY);
    auto socketConnector = SocketConnector(AF_INET, SOCK_STREAM);
    while (true) {
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        draw(pointVec, image);
        if (!socketConnector.connectToServer("172.17.0.1", 54000)) {
            cv::imwrite("name.jpeg", image);
        } else {
            cv::imencode("name.jpeg", image, imageVec);
            auto vecSender = VectorSender<uchar>(imageVec);
            vecSender.transferFile(
                [&](std::string data) {
                    if (data.size() > 4)
                        socketConnector.sendData(data, 20);
                    else
                        socketConnector.sendData(data, 3);
                },
                "name");
        }
        return 0;
    }