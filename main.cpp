#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"


static const int fps = 15;

int main() {
    cv::Mat frame;
    cv::VideoCapture vid(0);

    if (!vid.isOpened()) {
        return -1;
    }

    while (vid.read(frame)) {
        cv::imshow("Webcam", frame);

        if (cv::waitKey(1000 / fps) >= 0) {
            break;
        }
    }

    return 0;
}
