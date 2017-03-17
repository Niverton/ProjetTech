# ImageCropper 

## Summary

The ImageCropper utility is designed to crop a set of images from stereo videos, and assemble left part and right part as separated videos.

## Requirements

* FFmpeg (https://ffmpeg.org/).
* A compiler capable to compile C++11 code.
* CMake (https://cmake.org/).

### For Debian Jessie users

> sudo apt-get install cmake cmake-qt-gui

Get FFmpeg from the backports. Open your sources.list:

> sudo nano /etc/apt/sources.list

Add the following lines:

> \# jessie-backports  
> deb http://httpredir.debian.org/debian/ jessie-backports main contrib non-free

Run the following commands:

> sudo apt-get update  
> sudo apt-get install ffmpeg

Re-open your sources.list and comment the added lines:

> \# jessie-backports  
> \# deb http://httpredir.debian.org/debian/ jessie-backports main contrib non-free  

## Dependencies

* OpenCV 2.x (http://opencv.org/).

### For Debian Jessie users

Run the folowing command:

> sudo apt-get install libopencv-dev

Or manually build the version provided by on the OpenCV webnsite.

## Installation

Create a "build" directory if not present in the root directory of the ImageCropper project:

> mkdir build  
> cd build

Execute CMake:

> cmake ..

Then, execute Make:

> make

A "bin" directory should have been created by the make script. The executable "ImageCropper" lies here.

### Installation issues

Sometimes, even with a C++11 capable compiler, the Make script will fail. The compiler will claim that it is
not able to resolve some symbols which are part of C++11 new features. Rebuild the project using the following
commands:

> cmake-gui ..

Locate the CMAKE_CXX_FLAGS and enter "-std=c++11".
Push the "Configure" and "Generate" buttons.

> make

## Usage

In order to use the software, you first have to break down a stereo video into a set of frames. This is where FFmpeg
is handy. Run the following command:

> ffmpeg -i <video> <image-prefix>_<%04d>.png

Copy the absolute pathes of video frames into a file:

> ls -d -v $PWD/* > files.txt

Run the software in order to cut images:

> ./ImageCropper --help

Run the following command to assemble the left or right part of the video:

> ffmpeg -framerate 30 -i <image-prefix>-<%04d>.png <out>.mp4

## Author

Hadrien Decoudras - hdecoudras@gmail.com  
Public domain, Free use.