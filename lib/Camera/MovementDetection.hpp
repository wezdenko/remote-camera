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

    bool movementEnded;
    void (*func)(const std::vector<cv::Point2d> &);

  public:
    static const int MOVING = 0;
    static const int STATIONARY = 1;

  public:
    MovementDetection(int delay = 0, double maxError = 0.1);
    ~MovementDetection();

    void detectMovement(const cv::Point2d &currentPosition);
    bool isEndOfMovement() const;

    // sets function where the vector of points is sent after object stops
    // moving
    void setFunction(void (*func)(const std::vector<cv::Point2d> &));

    const std::vector<cv::Point2d> &getPoints() const;
    void clearPoints();

  private:
    void determineMovement(const cv::Point2d &currentPosition);
    void changeStateToStationary();
    void changeStateToMoving();
    void sendVector();
};
