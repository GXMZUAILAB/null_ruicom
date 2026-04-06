#include "LineProcessor.hpp"

LineProcessor::LineProcessor()
    : _threshold(60)
    , _roi(0, 0, 0, 0)
    , _blurKernel(5, 5)
{
    _morphKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
}

cv::Mat LineProcessor::process(const std::vector<uint8_t>& rawData)
{
    if (rawData.empty()) {
        return cv::Mat();
    }

    cv::Mat rawImg(rawData);
    cv::Mat img = cv::imdecode(rawImg, cv::IMREAD_COLOR);
    if (img.empty()) {
        return cv::Mat();
    }

    cv::Mat preprocessed = preprocess(img);
    cv::Mat binary = binarize(preprocessed);
    cv::Mat morphed = applyMorphology(binary);

    if (_roi.width > 0 && _roi.height > 0) {
        return morphed(_roi);
    }

    return morphed;
}

cv::Mat LineProcessor::preprocess(const cv::Mat& img)
{
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> channels;
    cv::split(hsv, channels);
    cv::Mat v = channels[2];

    cv::Mat blurred;
    cv::GaussianBlur(v, blurred, _blurKernel, 0);

    return blurred;
}

cv::Mat LineProcessor::binarize(const cv::Mat& gray)
{
    cv::Mat binary;
    cv::threshold(gray, binary, _threshold, 255, cv::THRESH_BINARY_INV);
    return binary;
}

cv::Mat LineProcessor::applyMorphology(const cv::Mat& binary)
{
    cv::Mat eroded, dilated;
    cv::erode(binary, eroded, _morphKernel, cv::Point(-1, -1), 1);
    cv::dilate(eroded, dilated, _morphKernel, cv::Point(-1, -1), 2);
    return dilated;
}

void LineProcessor::setConfig(int threshold, cv::Rect roi)
{
    _threshold = threshold;
    _roi = roi;
}

void LineProcessor::setThreshold(int threshold)
{
    _threshold = threshold;
}

void LineProcessor::setROI(cv::Rect roi)
{
    _roi = roi;
}