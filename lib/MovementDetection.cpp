#include "MovementDetection.hpp"
#include <iostream>

MovementDetection::MovementDetection() {
    this->lastPosition = cv::Point2d(-1, -1);
}

MovementDetection::~MovementDetection() {}

void MovementDetection::detectMovement(const cv::Point2d &currentPosition) {
    if (this->lastPosition != cv::Point2d(-1, -1)) {
        cv::Point2d delta = this->lastPosition - currentPosition;
        double err = delta.x * delta.x + delta.y * delta.y;

        if (err > 0.1) {
            this->points.push_back(currentPosition);
            std::cout << currentPosition.x << ", " << currentPosition.y << std::endl;
        }
    }

    this->lastPosition = currentPosition;
}