#include "ObjectDetection.hpp"
#include "MovementDetection.hpp"
#include <iostream>
#include <vector>


int main() {
    const int fps = 10;
    const int numOfEdges = 10;
    const int threshold = 230;

    cv::Mat frame;
    cv::VideoCapture vid(0);

    // default resolution is 640x480
    // to change that use:
    // vid.set(CAP_PROP_FRAME_WIDTH, width);
    // vid.set(CAP_PROP_FRAME_HEIGHT, height);

    if (!vid.isOpened()) {
        return -1;
    }

    ObjectDetection objDetection(threshold);
    MovementDetection mvDetection(fps * 3);
    cv::Point2d position;

    while (vid.read(frame)) {

        objDetection.loadFrame(frame);
        position = objDetection.detectObject(numOfEdges);

        mvDetection.detectMovement(position);

        if (cv::waitKey(1000 / fps) >= 0) {
            break;
        }
    }

    return 0;
}
