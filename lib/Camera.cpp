#include "Camera.hpp"

Camera::Camera(int fps, int numOfEdges, int threshold) {
    this->vid = cv::VideoCapture(0);

    // default resolution is 640x480
    // to change that use:
    // vid.set(CAP_PROP_FRAME_WIDTH, width);
    // vid.set(CAP_PROP_FRAME_HEIGHT, height);

    if (!vid.isOpened()) {
        throw "Couldn't connect to camera!";
    }

    this->fps = fps;
    this->numOfEdges = numOfEdges;
    this->objDetection = ObjectDetection(threshold);
}

Camera::~Camera() {}

cv::Point2d Camera::processFrame() {
    vid.read(this->frame);
    objDetection.loadFrame(this->frame);
    return objDetection.detectObject(this->numOfEdges);
}
