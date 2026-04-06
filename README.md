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