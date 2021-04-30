#include "MovementDetection.hpp"
#include <iostream>

MovementDetection::MovementDetection(int delay, double maxError) {
    this->lastPosition = cv::Point2d(-1, -1);
    this->delay = delay;
    this->maxError = maxError;
    this->framesWithoutMove = 0;
    this->state = MovementDetection::STATIONARY;
}

MovementDetection::~MovementDetection() {}

void MovementDetection::detectMovement(const cv::Point2d &currentPosition) {
    if (this->lastPosition != cv::Point2d(-1, -1)) {
        cv::Point2d delta = this->lastPosition - currentPosition;
        double positionChange = delta.x * delta.x + delta.y * delta.y;

        if (positionChange > this->maxError) {
            this->changeStateToMoving();
            this->framesWithoutMove = 0;
            this->points.push_back(currentPosition);
            std::cout << currentPosition.x << ", " << currentPosition.y
                      << std::endl;
        } else if (this->state == MOVING) {
            this->framesWithoutMove++;
        }

    } else if (this->state == MOVING) {
        this->framesWithoutMove++;
    }

    if (this->framesWithoutMove > this->delay) {
        this->changeStateToStationary();
    }

    std::cout << this->state << " : " << this->framesWithoutMove << std::endl;

    this->lastPosition = currentPosition;
}

void MovementDetection::changeStateToStationary() {
    if (this->state == MOVING) {
        this->state = STATIONARY;

        this->framesWithoutMove = 0;
        this->points.clear();
    }
}

void MovementDetection::changeStateToMoving() {
    if (this->state == STATIONARY) {
        this->state = MOVING;
    }
}