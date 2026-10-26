cmake_minimum_required(VERSION 3.10)

project(videoingest)

set(CMAKE_BUILD_TYPE Debug)

# 1. Ensure PkgConfig is available
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET
    gstreamer-1.0
    gstreamer-video-1.0
    gstreamer-app-1.0
)

pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET
    opencv4
)

add_executable(videoingest src/GstVideoIngest.cpp)

target_link_libraries(videoingest PRIVATE
    PkgConfig::GSTREAMER 
    PkgConfig::OPENCV
)

target_include_directories(videoingest PRIVATE include)