Unitree_SDK2 的官方仓库位置在 @unitree_sdk2/ ，可以在这里找到 Unitree_SDK2 的接口定义以及代码示例。

在完成代码更改（如编写完新功能或修复 Bug）后，请务必同步更新项目文档：
1. **README.md**：应包含仓库的整体架构描述，确保其与最新代码实现保持一致。
2. **docs/ 目录**：具体的模块使用说明、接口调用示例等详细文档应放在 `docs/` 目录下，不要放在 README 中。
3. **GEMINI.md**：应包含整个仓库的文件结构描述，并保持实时更新。

## 代码规范与注释要求

在编写或修改代码时，必须遵循以下注释规范：

1. **中文注释**：所有代码注释必须使用中文。
2. **函数级注释**：每个函数（包括构造函数、成员函数、全局函数）都必须添加规范的 Doxygen 风格注释，包含：
   - `@brief`：简要描述函数的功能。
   - `@param`：详细说明每个参数的含义及用途。
   - `@return`：说明返回值的含义（如果有）。
3. **关键逻辑注释**：对于函数内部复杂的算法步骤或关键逻辑块，需添加必要的行间注释。

示例：
```cpp
/**
 * @brief 计算线条质心横坐标
 * @param binary 输入的二值化图像
 * @return float 线条中心的x坐标，如果未检测到线条则返回 -1.0
 */
float getLineCenter(const cv::Mat& binary);
```

## 仓库文件结构描述

```text
.
├── GEMINI.md            # 本文件，存放 Agent 指令及仓库结构描述
├── CMakeLists.txt       # 项目 CMake 构建配置文件
├── README.md            # 项目自述文件，包含整体架构描述及环境准备说明
├── build/               # 编译构建目录（通常在 .gitignore 中忽略）
├── docs/                # 详细模块文档及使用说明目录
│   └── LineProcessor.md # LineProcessor 模块的使用示例与参数配置
├── include/             # 头文件目录
│   └── LineProcessor.hpp
├── src/                 # 源文件目录
    ├── LineProcessor.cpp
    ├── go2_video_client.cpp # 主程序入口，基于 Unitree SDK2 的视频客户端示例
    └── go2_sport_interactive.cpp # 交互式运动控制客户端，支持 Stretch 和 Hello

└── unitree_sdk2/        # Unitree SDK2 库及头文件
    ├── build/           # Build artifacts (binaries, CMake cache)
    ├── cmake/           # CMake configuration files
    ├── CMakeLists.txt   # Project CMake build configuration
    ├── example/         # Example code for different robot models and features
    │   ├── go2/         # Go2 robot examples
    │   ├── g1/          # G1 robot examples
    │   ├── h1/          # H1 robot examples
    │   ├── a2/          # A2 robot examples
    │   ├── b2/          # B2 robot examples
    │   └── ...
    ├── include/         # Header files
    │   └── unitree/     # Core SDK headers
    ├── lib/             # Compiled libraries
    ├── LICENSE          # License information
    ├── README.md        # Original SDK README
    └── thirdparty/      # Third-party dependencies
```