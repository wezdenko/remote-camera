#pragma once
#define MEMORY_SIZE 4
#define LIST_SIZE 250

class Point
{
    public:
        Point(double x, double y): xPos(x), yPos(y) {};
        double xPos;
        double yPos;
};

struct Shmbuf {
    Point   buf[MEMORY_SIZE][LIST_SIZE];
};