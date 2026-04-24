# Repository Structure

```text
.
├── AGENTS.md            # Agent instructions and context
├── CMakeLists.txt       # Project CMake build configuration
├── README.md            # Project overview and architecture
├── build/               # Build artifacts (ignored)
├── docs/                # Detailed module documentation
│   ├── LineProcessor.md # LineProcessor usage and tuning guide
│   └── safety_detection.md
├── include/             # Header files
│   ├── LineProcessor.hpp
│   └── YOLODetector.hpp
├── src/                 # Source files
│   ├── LineProcessor.cpp
│   ├── YOLODetector.cpp
│   ├── go2_video_client.cpp
│   ├── go2_sport_interactive.cpp
│   ├── go2_line_following.cpp # Line following tuning tool (realsense2)
│   ├── go2_safety_detection.cpp
│   ├── go2_light_controller.cpp
│   └── go2_obstacles_avoid.cpp
└── unitree_sdk2/        # Unitree SDK2 (Soft link)
```
