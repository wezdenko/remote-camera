#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "vector"


static const int fps = 15;

int main() {
    cv::Mat frame, grayFrame, drawing;
    cv::VideoCapture vid(0);

    // default resolution is 640x480
    // to change that use:
    // vid.set(CAP_PROP_FRAME_WIDTH, width);
    // vid.set(CAP_PROP_FRAME_HEIGHT, height);

    if (!vid.isOpened()) {
        return -1;
    }

    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> approxContours;

    cv::Scalar redColor(0, 0, 255);

    while (vid.read(frame)) {
        cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);

        cv::threshold(grayFrame, grayFrame, 230, 255, CV_THRESH_BINARY);

        cv::findContours(grayFrame, contours, hierarchy, cv::RETR_TREE,
                         CV_CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> contours_poly(contours.size());

        for (size_t i = 0; i < contours.size(); i++) {
            approxPolyDP(contours[i], contours_poly[i], 8, true);

            if (contours_poly[i].size() == 10) {
                cv::Moments m = cv::moments(contours[i]);
                cv::Point2d center(m.m10 / m.m00, m.m01 / m.m00);
                
                cv::drawContours(frame, contours_poly, (int)i, redColor, 2,
                                 cv::LINE_8, hierarchy, 0);
                cv::circle(frame, center, 4, redColor, -1);
            }
        }

        cv::imshow("Webcam", frame);

        if (cv::waitKey(1000 / fps) >= 0) {
            break;
        }
    }

    return 0;
}
