cmake_minimum_required(VERSION 3.5)
project(go2_video_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(UNITREE_SDK_PATH /home/nullsky/unitree_sdk2/lib/${CMAKE_SYSTEM_PROCESSOR})
find_library(UNITREE_SDK_LIB unitree_sdk2 PATHS ${UNITREE_SDK_PATH} NO_DEFAULT_PATH)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

add_library(ddsc SHARED IMPORTED GLOBAL)
set_target_properties(ddsc PROPERTIES IMPORTED_LOCATION ${UNITREE_SDK_PATH}/libddsc.so)

add_library(ddscxx SHARED IMPORTED GLOBAL)
set_target_properties(ddscxx PROPERTIES IMPORTED_LOCATION ${UNITREE_SDK_PATH}/libddscxx.so)

include_directories(/home/nullsky/unitree_sdk2/include)

add_executable(go2_video_client go2_video_client.cpp)
target_link_libraries(go2_video_client unitree_sdk2 ddsc ddscxx ${OpenCV_LIBS} Threads::Threads)
