#pragma once

#include <vector>
#include "opencv2/core/types.hpp" 

class MovementDetection
{
private:
    std::vector<cv::Point2d> points;
    cv::Point2d lastPosition;

public:
    MovementDetection();
    ~MovementDetection();

    void detectMovement(const cv::Point2d &currentPosition);

};


