# Go2 Video Client

基于 Unitree SDK2 的 Go2 机器人实时视频客户端。

## 依赖

- Unitree SDK2
- OpenCV 4.x

## 编译

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## 运行

确保机器人和 PC 在同一网络下：

```bash
./go2_video_client
```

按 `q` 或 `Esc` 退出。

## LineProcessor 使用示例

```cpp
#include "LineProcessor.hpp"

int main()
{
    unitree::robot::ChannelFactory::Instance()->Init(0);
    unitree::robot::go2::VideoClient video_client;
    video_client.SetTimeout(1.0f);
    video_client.Init();

    LineProcessor processor;
    processor.setConfig(60, cv::Rect(0, 240, 640, 240));

    std::vector<uint8_t> image_sample;
    cv::Mat mask;

    while (true) {
        video_client.GetImageSample(image_sample);
        mask = processor.process(image_sample);

        if (!mask.empty()) {
            cv::imshow("Mask", mask);
        }

        char key = (char)cv::waitKey(1);
        if (key == 'q' || key == 27) break;
    }

    return 0;
}
```