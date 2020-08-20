/*
 * Copyright (C) 2016 Love Park Robotics, LLC
 * Copyright (C) 2017 ifm syntron gmbh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distribted on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// pcl_io.cpp
//
// Capture frames from the camera, and write the data out to PCL files.
//

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

int main(int argc, const char **argv)
{
  std::cout << "Hello from pcl_io application!" << std::endl;

  // parse command line arguments
  if (argc <= 1)
  {
    std::cout << "No folder path provided, exiting ..." << std::endl;
    exit(EXIT_FAILURE);
  }
  // check if image destination folder exists
  std::string imageDirectory = argv[1];
  if (!std::filesystem::exists(imageDirectory))
  {
    std::cout << "Folder does not exist, exiting ..." << std::endl;
    exit(EXIT_FAILURE);
  }  

  auto cam = ifm3d::Camera::MakeShared();

  ifm3d::ImageBuffer::Ptr img = std::make_shared<ifm3d::ImageBuffer>();
  ifm3d::FrameGrabber::Ptr fg = std::make_shared<ifm3d::FrameGrabber>(cam, ifm3d::IMG_AMP|ifm3d::IMG_CART|ifm3d::IMG_RDIS);

  std::cout << "Press enter to take image, enter 'e' to exit: ";
  for (int indexImage = 1, ch; (ch = std::cin.get()) != EOF && ch != 'e'; indexImage++)
  {        
    if (ch != '\n')
      while (std::cin.get() != '\n');
    
    if (! fg->WaitForFrame(img.get(), 1000))
    {
      std::cerr << "Timeout waiting for camera!" << std::endl;
      return -1;
    }

    pcl::PointCloud<ifm3d::PointT>::Ptr ptrPC = img->Cloud();
    
    // write point cloud to disk
    std::string fileName = imageDirectory + "/point_cloud_" + std::to_string(indexImage) + ".ply";
    pcl::PLYWriter writer;
    writer.write(fileName, *ptrPC);    
    
    std::cout << "Press enter to take image, enter 'e' to exit: ";
  }
  std::cout << "Exiting\n";

  return 0;
}
