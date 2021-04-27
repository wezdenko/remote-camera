#include "ObjectDetection.hpp"
#include <vector>


int main() {
    const int fps = 15;
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
    cv::Point2d lastPosition;

    while (vid.read(frame)) {

        objDetection.loadFrame(frame);
        lastPosition = objDetection.detectObject(numOfEdges);

        if (cv::waitKey(1000 / fps) >= 0) {
            break;
        }
    }

    return 0;
}
