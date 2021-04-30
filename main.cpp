#include "Camera.hpp"
#include "MovementDetection.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>


int main() {
    Camera camera(10, 10, 230);
    cv::Point2d point;

    while (true) {
        point = camera.processFrame();
        std::cout << point << std::endl;

        usleep(200 * 1000);
    }

    return 0;
}
