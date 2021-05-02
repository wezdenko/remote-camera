#pragma once
#define MEMORY_SIZE 25
#define LIST_SIZE 250

#include <vector>

class Point
{
    public:
        Point(): xPos(0), yPos(0){};
        Point(double x, double y): xPos(x), yPos(y) {};
        double xPos;
        double yPos;
};

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