#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "LineProcessor.hpp"

// Global parameters for trackbars
int g_threshold = 60;
int g_hsv_channel = 2; // V channel
int g_roi_y = 300;
int g_roi_h = 100;
int g_erode_iter = 1;
int g_dilate_iter = 2;

void on_trackbar(int, void*) {}

int main(int argc, char** argv)
{
    // Initialize LineProcessor
    LineProcessor processor;

    // Configure RealSense pipeline
    rs2::pipeline pipe;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    try {
        pipe.start(cfg);
    } catch (const rs2::error & e) {
        std::cerr << "无法启动 RealSense 设备: " << e.what() << std::endl;
        return -1;
    }

    // Create Tuning Window
    std::string win_tuning = "Tuning Controls";
    cv::namedWindow(win_tuning, cv::WINDOW_NORMAL);
    cv::createTrackbar("Threshold", win_tuning, &g_threshold, 255, on_trackbar);
    cv::createTrackbar("HSV Channel", win_tuning, &g_hsv_channel, 2, on_trackbar);
    cv::createTrackbar("ROI Y Offset", win_tuning, &g_roi_y, 470, on_trackbar);
    cv::createTrackbar("ROI Height", win_tuning, &g_roi_h, 480, on_trackbar);
    cv::createTrackbar("Erode Iter", win_tuning, &g_erode_iter, 10, on_trackbar);
    cv::createTrackbar("Dilate Iter", win_tuning, &g_dilate_iter, 10, on_trackbar);

    cv::namedWindow("Line Following View", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Binary Mask (ROI)", cv::WINDOW_AUTOSIZE);

    std::cout << "控制说明: [q/Esc] 退出程序" << std::endl;

    while (true)
    {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::frame color_frame = frames.get_color_frame();

        if (!color_frame) continue;

        cv::Mat frame(cv::Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
        
        // Update processor settings from trackbars
        processor.setThreshold(g_threshold);
        processor.setHSVChannel(g_hsv_channel);
        processor.setMorphIterations(g_erode_iter, g_dilate_iter);
        
        int roi_y = std::clamp(g_roi_y, 0, frame.rows - 1);
        int roi_h = std::clamp(g_roi_h, 1, frame.rows - roi_y);
        processor.setROI(cv::Rect(0, roi_y, frame.cols, roi_h));

        // Process frame
        cv::Mat binary_roi = processor.process(frame);

        // Calculate line center
        float cx = processor.getLineCenter(binary_roi);

        // Visualization
        cv::Mat display = frame.clone();
        
        // Draw ROI rectangle
        cv::rectangle(display, cv::Rect(0, roi_y, frame.cols, roi_h), cv::Scalar(0, 255, 255), 2);

        if (cx >= 0) {
            // Draw detected center
            cv::circle(display, cv::Point((int)cx, roi_y + roi_h / 2), 5, cv::Scalar(0, 0, 255), -1);
            
            // Draw vertical guide line
            cv::line(display, cv::Point((int)cx, roi_y), cv::Point((int)cx, roi_y + roi_h), cv::Scalar(0, 255, 0), 2);
            
            // Show error from center
            float error = cx - (frame.cols / 2.0f);
            std::string text = "Offset: " + std::to_string((int)error);
            cv::putText(display, text, cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(display, "LINE LOST!", cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("Line Following View", display);
        if (!binary_roi.empty()) {
            cv::imshow("Binary Mask (ROI)", binary_roi);
        }

        char key = (char)cv::waitKey(1);
        if (key == 'q' || key == 27) break;
    }

    cv::destroyAllWindows();
    return 0;
}
