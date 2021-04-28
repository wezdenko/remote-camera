#pragma once

#include "opencv2/core/types.hpp"
#include <vector>

class MovementDetection {
  private:
    std::vector<cv::Point2d> points;
    cv::Point2d lastPosition;

    double maxError;
    int delay;
    int framesWithoutMove;
    int state;

  public:
    static const int MOVING = 0;
    static const int STATIONARY = 1;

  public:
    MovementDetection(int delay, double maxError = 0.1);
    ~MovementDetection();

    void detectMovement(const cv::Point2d &currentPosition);

  private:
    void changeStateToStationary();
    void changeStateToMoving();
};
