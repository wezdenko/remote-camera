#include "MovementDetection.hpp"
#include "ObjectDetection.hpp"

class Camera {
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

    bool isEndOfMovement() const;
    void processFrame();
    void setFunction(void (*func)(const std::vector<cv::Point2d> &));
    const std::vector<cv::Point2d> &getPoints() const;
    void clearPoints();
};
