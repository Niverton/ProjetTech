cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)

project(ImageCropper)

set(SOURCES 
    sources/imagecropper.cpp
    sources/main.cpp
    )

set (HEADERS
    includes/imagecropper.h
    )

include_directories(${OPENCV_INCLUDE_DIRS} includes)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(ImageCropper ${SOURCES} ${HEADERS})

target_link_libraries(ImageCropper ${OpenCV_LIBS})

