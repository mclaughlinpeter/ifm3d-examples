cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0048 NEW)

project(pcl_io CXX)

# Global compiler flags
set(CMAKE_BUILD_TYPE Release) # Release or Debug
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(FORCE_OPENCV3)
  find_package(OpenCV 3 REQUIRED)
elseif(FORCE_OPENCV2)
  find_package(OpenCV 2.4 REQUIRED)
else()
  find_package(OpenCV REQUIRED)
endif()

##############################################################
## finding the ifm3d lib.
##############################################################
find_package(ifm3d 0.11.0 CONFIG
  REQUIRED COMPONENTS camera framegrabber image
  )

##############################################################
## finding the boost libs
##############################################################
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

##############################################################
## finding the pcl libs
##############################################################
find_package(PCL REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcl_io pcl_io.cpp)
target_link_libraries(pcl_io
                      ifm3d::camera
                      ifm3d::framegrabber
                      ifm3d::image
                      ${OpenCV_LIBRARIES}
		                  ${Boost_LIBRARIES}
		                  ${PCL_LIBRARIES}
                      -lstdc++fs
                      )