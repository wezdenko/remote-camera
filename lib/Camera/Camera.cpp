#include "Camera.hpp"

Camera::Camera(int numOfEdges, int threshold, int delay, double maxError) {
    this->vid = cv::VideoCapture(0);

    // default resolution is 640x480
    // to change that use:
    // vid.set(CAP_PROP_FRAME_WIDTH, width);
    // vid.set(CAP_PROP_FRAME_HEIGHT, height);

    if (!vid.isOpened()) {
        throw "Couldn't connect to camera!";
    }

    this->numOfEdges = numOfEdges;
    this->objDetection = ObjectDetection(threshold);
    this->movDetection = MovementDetection(delay, maxError);
}

Camera::~Camera() {}

void Camera::processFrame() {
    vid.read(this->frame);
    objDetection.loadFrame(this->frame);
    cv::Point2d position = objDetection.detectObject(this->numOfEdges);
    this->movDetection.detectMovement(position);
}

void Camera::setFunction(void (*func)(const std::vector<cv::Point2d> &)) {
    this->movDetection.setFunction(func);
}
bool Camera::isEndOfMovement() const{
    return this->movDetection.isEndOfMovement();
};
