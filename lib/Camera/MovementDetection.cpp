#include "MovementDetection.hpp"

MovementDetection::MovementDetection(int delay, double maxError) {
    this->lastPosition = cv::Point2d(-1, -1);
    this->delay = delay;
    this->maxError = maxError;
    this->framesWithoutMove = 0;
    this->state = MovementDetection::STATIONARY;
    this->func = NULL;
    this->movementEnded = false;
}

MovementDetection::~MovementDetection() {}

void MovementDetection::detectMovement(const cv::Point2d &currentPosition) {
    movementEnded = false;

    // if last position was observed
    if (currentPosition != cv::Point2d(-1, -1)) {
        this->determineMovement(currentPosition);
    }
    // if no last position and state is moving
    else if (this->state == MOVING) {
        this->framesWithoutMove++;
    }

    if (this->framesWithoutMove > this->delay) {
        this->changeStateToStationary();
    }

    this->lastPosition = currentPosition;
}

bool MovementDetection::isEndOfMovement() const {
    return this->movementEnded;
}

void MovementDetection::setFunction(
    void (*func)(const std::vector<cv::Point2d> &)) {

    this->func = func;
}

const std::vector<cv::Point2d> &MovementDetection::getPoints() const {
    return this->points;
}

void MovementDetection::clearPoints() {
    this->points.clear();
}

void MovementDetection::determineMovement(const cv::Point2d &currentPosition) {
    cv::Point2d delta = this->lastPosition - currentPosition;
    double positionChange = delta.x * delta.x + delta.y * delta.y;

    if (positionChange > this->maxError) {
        this->changeStateToMoving();
        this->framesWithoutMove = 0;
        this->points.push_back(currentPosition);
    } else if (this->state == MOVING) {
        this->framesWithoutMove++;
    }
}

void MovementDetection::changeStateToStationary() {
    if (this->state == MOVING) {
        this->state = STATIONARY;

        this->framesWithoutMove = 0;
        // this->sendVector();
        this->movementEnded = true;
    }
}

void MovementDetection::changeStateToMoving() {
    if (this->state == STATIONARY) {
        this->state = MOVING;
    }
}

void MovementDetection::sendVector() {
    if (func != NULL) {
        this->func(this->points);
    }
    this->points.clear();
}