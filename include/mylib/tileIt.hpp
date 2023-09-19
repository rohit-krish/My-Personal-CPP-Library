#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include <string>

namespace mylib
{
    typedef struct
    {
        cv::Mat img;
        std::string label = "";
    } DisObj_t;

    cv::Mat tileIt(const std::vector<std::vector<DisObj_t>> &dis_obj, float imgScale = 1.0, short labelHeight = 30, float labelScale = 0.8, int labelThickness = 1);
}
