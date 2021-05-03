#include "ObjectDetection.hpp"
#include "MovementDetection.hpp"

class Camera
{
private:
    cv::Mat frame;
    cv::VideoCapture vid;

    int fps;
    int numOfEdges;

    ObjectDetection objDetection;
    MovementDetection movDetection;

    cv::Point2d position;

public:
    Camera(int numOfEdges, int threshold, int delay, double maxError);
    ~Camera();

    void processFrame();
    void setFunction(void (*func)(const std::vector<cv::Point2d> &));
};

