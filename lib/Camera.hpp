#include "ObjectDetection.hpp"

class Camera
{
private:
    cv::Mat frame;
    cv::VideoCapture vid;

    int fps;
    int numOfEdges;

    ObjectDetection objDetection;
    cv::Point2d position;

public:
    Camera(int fps, int numOfEgdes, int threshold);
    ~Camera();

    cv::Point2d processFrame();
};

