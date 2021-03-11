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
#include <vector>

#include <opencv2/opencv.hpp>
#include <ifm3d/camera.h>
#include <ifm3d/fg.h>
#include <ifm3d/image.h>

#include <pcl/pcl_exports.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/file_io.h>

extern "C" {
    class LIB_API IfmCamera
    {
    private:
        ifm3d::Camera::Ptr cam;
        ifm3d::ImageBuffer::Ptr img;
        ifm3d::FrameGrabber::Ptr fg;
        std::vector<std::vector<float>> ConvertToXYZ(pcl::PointCloud<ifm3d::PointT>::Ptr ptrPC);
    public:
        IfmCamera();
        ~IfmCamera();
        void GrabAndSaveImages(std::string imageDirectory);
        std::vector<std::vector<float>> GrabImage();
    };
}

#endif