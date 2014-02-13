CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(name "genderRecognizer")
set(the_library "opencv_${name}")
project(${the_library})

#SET(OpenCV_DIR /path/to/your/opencv/installation)

#---------------------------------
# packages
#---------------------------------
find_package(OpenCV REQUIRED) 

#---------------------------------
# includes & sources
#---------------------------------
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB lib_hdrs "*.h")
file(GLOB lib_srcs "*.cpp")

#---------------------------------
# build the library & link
#---------------------------------
add_library(${the_library} ${lib_srcs} ${lib_hdrs})
target_link_libraries(${the_library} opencv_core opencv_imgproc opencv_highgui)
