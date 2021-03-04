#ifndef PCL_IO_LIBRARY_HPP
#define PCL_IO_LIBRARY_HPP

#ifndef LIB_API
#define LIB_API __attribute__((visibility("default")))
#endif

#include <iostream>
#include <memory>
#include <cstdlib>
#include <filesystem>
#include <string>

#include <opencv2/opencv.hpp>
#include <ifm3d/camera.h>
#include <ifm3d/fg.h>
#include <ifm3d/image.h>

#include <pcl/pcl_exports.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/file_io.h>

extern "C" LIB_API void capture(std::string imageDirectory);

#endif