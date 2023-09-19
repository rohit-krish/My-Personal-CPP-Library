#include <mylib/tileIt.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);

    cv::namedWindow("window", cv::WINDOW_NORMAL);

    if (!cap.isOpened())
    {
        std::cerr << "Error opening video stream :(";
        return 0;
    }

    cv::Mat frame;

    while (true)
    {
        cap.read(frame);

        if (frame.empty())
            break;

        std::vector<std::vector<mylib::DisObj_t>> dis_obj = {{{frame, "Zero"}}, {{frame}, {frame, "Three"}}, {{frame}, {frame}, {frame, "Six"}}, {{frame}, {frame}, {frame}, {frame, "Nine"}}};
        cv::Mat stackedImage = mylib::tileIt(dis_obj, 1, 30, .9, 2);

        cv::imshow("window", stackedImage);

        auto key = cv::waitKey(1);

        if (key == (int8_t)'q')
            break;
        else if (key == (int8_t)' ')
            cv::waitKey(0);
    }

    return 0;
}
