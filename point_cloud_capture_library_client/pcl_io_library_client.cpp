#include <iostream>
#include "pcl_io_library.hpp"

int main(int argc, const char **argv)
{
    std::cout << "Hello from main()" << std::endl;

    IfmCamera ifmCamera;
    ifmCamera.GrabImage("images");

    //capture("images");

    return 0;
}

// g++ -I. -I/home/peter/ifm3d-examples/point_cloud_capture_library -I/usr/include/pcl-1.8 -I/usr/include/eigen3 pcl_io_library_client.cpp -o pcl_io_library_client -L/home/peter/ifm3d-examples/build/point_cloud_capture_library -lpcl_io_library -L/usr/lib/x86_64-linux-gnu -lpcl_common -lpcl_io -lboost_system -lglog -lopencv_core -L/usr/lib -lifm3d_camera -lifm3d_framegrabber -lifm3d_image -lstdc++fs