#pragma once

const char* MEMORY_NAME = "/memory";
const unsigned BUFFER_LENGTH = 25;
const unsigned POINTS_NUMBER = 250;

class Point
{
    public:
        Point(double x, double y): xPos(x), yPos(y) {};
        double xPos;
        double yPos;
};

struct Shmbuf {
    Point   buf[BUFFER_LENGTH][POINTS_NUMBER];
};