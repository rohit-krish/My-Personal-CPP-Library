#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <string>
#include <iostream>

namespace mylib
{
    typedef struct
    {
        cv::Mat img;
        std::string label = "";
    } DisObj_t;

    bool has_text_in_row_func(std::vector<std::vector<DisObj_t>> dis_obj, short index)
    {
        if (index < 0 || index >= (short)dis_obj.size())
            return false;

        for (DisObj_t &obj : dis_obj[index])
            if (obj.label != "")
                return true;

        return false;
    }

    cv::Mat tileIt(const std::vector<std::vector<DisObj_t>> &dis_obj, float imgScale = 1.0, short labelHeight = 30, float labelScale = 0.8, int labelThickness = 1)
    {
        /*
        >>> cv::Mat img1 = cv::imread("../assets/lenna.png");
        >>> cv::Mat img2 = cv::imread("../assets/ironmanShield.jpg");

        >>> std::vector<std::vector<mylib::DisObj_t>> dis_obj = {{{img1}, {img2}}, {{img2, "ironman"}, {img1}}};
        >>> cv::Mat tiledImages = mylib::tileIt(dis_obj, 1, 30, 1, 1);

        >>> cv::namedWindow("Images", cv::WINDOW_NORMAL);
        >>> cv::imshow("Images", tiledImages);
        >>> cv::waitKey(0);
        */

        short unsigned nRows = dis_obj.size();
        short unsigned nCols = 0;
        bool has_text_in_row[nRows];
        short unsigned total_label_count = 0;

        for (short i = 0; i < nRows; i++)
        {
            has_text_in_row[i] = has_text_in_row_func(dis_obj, i);
            total_label_count += has_text_in_row[i];
            if ((short)dis_obj[i].size() > nCols)
                nCols = dis_obj[i].size();
        }

        short unsigned height = (short)(dis_obj[0][0].img.rows * imgScale);
        short unsigned width = (short)(dis_obj[0][0].img.cols * imgScale);

        cv::Mat result((nRows * height) + (labelHeight * total_label_count), nCols * width, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::Mat img, combined;

        short unsigned rect_y = 0;
        // short unsigned rect_y = height + (labelHeight * has_text_in_row[0]);

        for (short rIdx = 0; rIdx < nRows; rIdx++)
        {
            for (short cIdx = 0; cIdx < nCols; cIdx++)
            {
                if (rIdx < (short)dis_obj.size() && cIdx < (short)dis_obj[rIdx].size())
                {
                    img = dis_obj[rIdx][cIdx].img.clone();

                    if (img.channels() == 1)
                        cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

                    cv::resize(img, img, cv::Size(width, height));

                    if (dis_obj[rIdx][cIdx].label == "")
                    {
                        if (has_text_in_row[rIdx])
                        {
                            combined.release(); // clear the data but preserve the allocated space
                            cv::Mat textPlace(labelHeight, width, CV_8UC3, cv::Scalar(0, 0, 0));
                            cv::vconcat(img, textPlace, combined);
                            combined.copyTo(result(cv::Rect(cIdx * width, rect_y, width, height + labelHeight)));
                        }
                        else
                        {
                            img.copyTo(result(cv::Rect(cIdx * width, rect_y, width, height)));
                        }
                    }
                    else
                    {
                        combined.release(); // clear the data but preserve the allocated space
                        cv::Mat textPlace(labelHeight, width, CV_8UC3, cv::Scalar(0, 0, 0));
                        cv::putText(textPlace, dis_obj[rIdx][cIdx].label, cv::Point(10, labelHeight - 5), cv::FONT_HERSHEY_SIMPLEX, labelScale, cv::Scalar(255, 255, 255), labelThickness);
                        cv::vconcat(img, textPlace, combined);
                        combined.copyTo(result(cv::Rect(cIdx * width, rect_y, width, height + labelHeight)));
                    }
                }
            }
            rect_y = (rIdx + 1) * (height + (labelHeight * has_text_in_row[rIdx]));
        }

        return result;
    }
} // namespace mylib

