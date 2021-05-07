#pragma once

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

class ObjectDetection {
  private:
    cv::Mat *frame;
    int threshold;

    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> approxContours;

  public:
    ObjectDetection(int threshold = 0);
    ~ObjectDetection();

    void loadFrame(cv::Mat &frame);
    cv::Point2d detectObject(int numOfEdges);

  private:
    cv::Point2d getObjectCenter(int numOfEdges);
};
