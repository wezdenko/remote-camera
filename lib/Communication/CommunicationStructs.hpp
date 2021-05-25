#pragma once
#define MEMORY_SIZE 25
#define LIST_SIZE 250

#include "opencv2/core/types.hpp"
#include <vector>

using Point = cv::Point2d;


class MoveBuffer {
  public:
    MoveBuffer();
    MoveBuffer(const std::vector<Point> &points) { transferToBuffer(points); };
    inline void transferToBuffer(const std::vector<Point> &points) {
        for (int i = 0; i < LIST_SIZE; i++) {
            buf[i] = Point(-1.0, -1.0);
        }
        for (int i = 0; i < points.size(); i++) {
            buf[i] = points[i];
        }
    };
    inline std::vector<Point> transferBufferToVector() {
        std::vector<Point> points;
        Point point;
        for (int i = 0; i < LIST_SIZE; i++) {
            point = buf[i];
            if (point.x != -1.0)
                points.push_back(Point(point));
        }
        return points;
    };

  private:
    Point buf[LIST_SIZE];
};

struct Shmbuf {
    MoveBuffer buf[MEMORY_SIZE];
};