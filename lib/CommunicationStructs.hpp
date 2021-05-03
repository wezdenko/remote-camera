#pragma once
#define MEMORY_SIZE 25
#define LIST_SIZE 250

#include <vector>
#include "opencv2/core/types.hpp"

using Point = cv::Point2d;


class MoveBuffer{
    public:
        MoveBuffer();
        MoveBuffer(const std::vector<Point>& points){
            transferToBuffer(points);
        };
        inline void transferToBuffer(const std::vector<Point>& points){
            for(int i=0; i<LIST_SIZE; i++){
                buf[i] = Point(points[i]);
            }
        }
        Point buf[250];
};

struct Shmbuf {
    MoveBuffer   buf[MEMORY_SIZE];
};