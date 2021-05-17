#include "Communication/CommunicationStructs.hpp"
#include "Communication/Memory/MemoryConsumer.hpp"
#include "Communication/Queue/QueReceiver.hpp"
#include "Def.h"
#include "FileLib/Date.hpp"
#include "FileLib/FileDetector.hpp"
#include "FileLib/FileSender.hpp"
#include "FileLib/VectorSender.hpp"
#include "Socket/SocketConnector.hpp"
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


std::vector<std::string> getRemainingImagesNames();
void sendRemainingFiles(const std::vector<std::string> &names);
void sendMemoryImage(const std::vector<uchar> &imageVec,
                     const std::string &date, SocketConnector& socketConnector);
bool isConnection();
void draw(const std::vector<cv::Point2d> &points, cv::Mat &img);


int main() {

    cv::Scalar backgroundColor(255, 255, 255); // white

    cv::Mat image(HEIGHT, WIDTH, CV_8UC3, backgroundColor);
    std::vector<uchar> imageVec;

    auto memory = MemoryConsumer(MEMORY_NAME);
    auto que = QueReceiver(QUEUE_NAME, O_CREAT | O_RDONLY);
    while (true) {
        auto index = que.reciveData();
        auto pointVec = memory.getFromMemory(std::stoi(index));
        image = backgroundColor;
        draw(pointVec, image);
        auto date = Date::getTime();
        auto socketConnector = SocketConnector(AF_INET, SOCK_STREAM);
        if (!socketConnector.connectToServer(IP_ADDR, PORT)) {
            cv::imwrite(date + FILE_TYPE, image);
        } else {
            cv::imencode(date + FILE_TYPE, image, imageVec);
            sendMemoryImage(imageVec, date, socketConnector);
            socketConnector.closeConnection();
            sendRemainingFiles(getRemainingImagesNames());
        }
    }
    return 0;
}

std::vector<std::string> getRemainingImagesNames() {
    auto isImage = [](std::string &name) -> bool {
        auto jpegLocation = name.find(FILE_TYPE);
        if (jpegLocation == 27) {
            name = name.substr(2, jpegLocation - 2);
            return true;
        }
        return false;
    };
    FileDetector fileDetector(".");
    return fileDetector.getFilesName(isImage);
}


void sendRemainingFiles(const std::vector<std::string> &names) {
    auto fileSender = FileSender();
    for (const auto &file : names) {
        auto socketConnector = SocketConnector(AF_INET, SOCK_STREAM);
        if (socketConnector.connectToServer(IP_ADDR, PORT)) {
            fileSender.transferFile(
                [&](std::string data) {
                    if (data.size() > DATA_SIZE)
                        socketConnector.sendData(data, FILE_NAME_SIZE);
                    else
                        socketConnector.sendData(data, DATA_SIZE);
                },
                file);
            socketConnector.closeConnection();
            std::string fileName = file + FILE_TYPE;
            std::remove(fileName.c_str());
        }
    };
}

void sendMemoryImage(const std::vector<uchar> &imageVec,
                     const std::string &date, SocketConnector& socketConnector) {
        auto vecSender = VectorSender<uchar>(imageVec);
        vecSender.transferFile(
            [&](std::string data) {
                if (data.size() > DATA_SIZE)
                    socketConnector.sendData(data, FILE_NAME_SIZE);
                else
                    socketConnector.sendData(data, DATA_SIZE);
            },
            date);
}

void draw(const std::vector<cv::Point2d> &points, cv::Mat &img) {
    const cv::Scalar imgColor(0, 0, 0);
    const cv::Scalar lineColor(0, 0, 255);

    const cv::Point2d *lastPoint = &points.front();

    for (const cv::Point2d &point : points) {
        cv::line(img, *lastPoint, point, lineColor);
        lastPoint = &point;
    }
}
