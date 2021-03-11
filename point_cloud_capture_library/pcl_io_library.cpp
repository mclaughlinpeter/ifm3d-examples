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

#include "pcl_io_library.hpp"

IfmCamera::IfmCamera()
{
    cam = ifm3d::Camera::MakeShared();

    img = std::make_shared<ifm3d::ImageBuffer>();
    fg = std::make_shared<ifm3d::FrameGrabber>(cam, ifm3d::IMG_AMP|ifm3d::IMG_CART|ifm3d::IMG_RDIS);
}

IfmCamera::~IfmCamera()
{

}

void IfmCamera::GrabAndSaveImages(std::string imageDirectory)
{
    std::cout << "Hello from pcl_io application!" << std::endl;

    // check if image destination folder exists
    if (!std::filesystem::exists(imageDirectory))
    {
        std::cout << "Folder does not exist, exiting ..." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Press enter to take image, enter 'e' to exit: ";
    for (int indexImage = 1, ch; (ch = std::cin.get()) != EOF && ch != 'e'; indexImage++)
    {
        if (ch != '\n')
            while (std::cin.get() != '\n');

        if (! fg->WaitForFrame(img.get(), 1000))
        {
            std::cerr << "Timeout waiting for camera!" << std::endl;
            return;
        }

        pcl::PointCloud<ifm3d::PointT>::Ptr ptrPC = img->Cloud();

        // write point cloud to disk
        std::string fileName = imageDirectory + "/point_cloud_" + std::to_string(indexImage) + ".ply";
        pcl::PLYWriter writer;
        writer.write(fileName, *ptrPC);

        std::cout << "Press enter to take image, enter 'e' to exit: ";
    }
    std::cout << "Exiting\n";
}

std::vector<std::vector<float>> IfmCamera::GrabImage()
{
    // TODO check if camera initialized

    if (! fg->WaitForFrame(img.get(), 1000))
    {
        std::cerr << "Timeout waiting for camera!" << std::endl;
    }
    
    pcl::PointCloud<ifm3d::PointT>::Ptr ptrPC = img->Cloud();

    return ConvertToXYZ(ptrPC);
}

std::vector<std::vector<float>> IfmCamera::ConvertToXYZ(pcl::PointCloud<ifm3d::PointT>::Ptr ptrPC)
{
    // extract raw point cloud data
    std::vector<ifm3d::PointT, Eigen::aligned_allocator<ifm3d::PointT>> data = ptrPC->points;
    std::size_t noOfPoints = data.size();

    // create structure using std::vector
    std::vector<std::vector<float>> dataXYZ(3, std::vector<float>(noOfPoints, 0.0F));

    for (size_t i = 0; i < noOfPoints; i++)
    {
        dataXYZ[0][i] = data[i].x;
        dataXYZ[1][i] = data[i].y;
        dataXYZ[2][i] = data[i].z;
    }

    return dataXYZ;
}
