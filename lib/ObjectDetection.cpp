#include "ObjectDetection.hpp"

ObjectDetection::ObjectDetection(int threshold) {
    this->frame = NULL;
    this->threshold = threshold;
}

ObjectDetection::~ObjectDetection() {}

void ObjectDetection::loadFrame(cv::Mat &frame) { this->frame = &frame; }

cv::Point2d ObjectDetection::detectObject(int numOfEdges) {
    if (this->frame == NULL) {
        return cv::Point2d(-1, -1);
    }

    cv::Mat grayFrame;

    cv::cvtColor(*(this->frame), grayFrame, CV_BGR2GRAY);
    cv::threshold(grayFrame, grayFrame, this->threshold, 255, CV_THRESH_BINARY);
    cv::findContours(grayFrame, this->contours, this->hierarchy, cv::RETR_TREE,
                     CV_CHAIN_APPROX_SIMPLE);

    return this->getObjectCenter(numOfEdges);
}

cv::Point2d ObjectDetection::getObjectCenter(int numOfEdges) {
    std::vector<std::vector<cv::Point>> contours_poly(this->contours.size());

    for (size_t i = 0; i < this->contours.size(); i++) {
        approxPolyDP(this->contours[i], contours_poly[i], 8, true);

        if (contours_poly[i].size() == numOfEdges) {
            cv::Moments m = cv::moments(this->contours[i]);
            cv::Point2d center(m.m10 / m.m00, m.m01 / m.m00);

            return center;
        }
    }

    return cv::Point2d(-1, -1);
}