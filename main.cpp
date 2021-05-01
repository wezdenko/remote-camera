#include "Camera.hpp"
#include "MovementDetection.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>


int main() {
    int fps = 5;
    int numOfEdges = 10;
    int threshold = 230;
    int delay = fps * 3;
    double maxError = 0.1;

    Camera camera(numOfEdges, threshold, delay, maxError);

    while (true) {
        camera.processFrame();

        usleep((1000 / fps) * 1000);
    }

    return 0;
}
