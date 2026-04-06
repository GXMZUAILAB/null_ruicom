#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>

class LineProcessor
{
public:
    LineProcessor();

    cv::Mat process(const std::vector<uint8_t>& rawData);

    void setConfig(int threshold, cv::Rect roi);
    void setThreshold(int threshold);
    void setROI(cv::Rect roi);

private:
    cv::Mat preprocess(const cv::Mat& img);
    cv::Mat binarize(const cv::Mat& gray);
    cv::Mat applyMorphology(const cv::Mat& binary);

    int _threshold;
    cv::Rect _roi;
    cv::Size _blurKernel;
    cv::Mat _morphKernel;
};