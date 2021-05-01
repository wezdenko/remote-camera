#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>


void draw(const std::vector<cv::Point2d> &points, cv::Mat &img) {
    const cv::Scalar imgColor(0, 0, 0);
    const cv::Scalar lineColor(0, 0, 255);

    const cv::Point2d *lastPoint = &points.front();

    for (const cv::Point2d &point : points) {
        cv::line(img, *lastPoint, point, lineColor);
        lastPoint = &point;
    }
}

int main() {
    // shared memory with camera process
    // pointer to array and array length
    // ...

    // convert array to vector
    std::vector<cv::Point2d> points;

    // create image
    int width = 640;
    int height = 480;
    cv::Scalar backgroundColor(255, 255, 255); // white

    cv::Mat image(width, height, CV_8UC3, backgroundColor);

    // draw lines on the image
    draw(points, image);

    // shared memory with socket process
    // ...

    // writing image to buffer
    // buffer must be a vector of uchars
    std::vector<uchar> buff;
    cv::imencode("name.jpeg", image, buff);

    // create list of uchars in shared memory
    // convert vector to this list
    // ...

    return 0;
}