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
include_directories( "lib/" )

file(GLOB lib_hdrs "*.h")
file(GLOB lib_srcs "*.cpp")

#---------------------------------
# build the library & link
#---------------------------------
add_library(${the_library} ${lib_srcs} ${lib_hdrs})
target_link_libraries(${the_library} opencv_core opencv_imgproc opencv_highgui)


#---------------------------------
# add  simple examples
#---------------------------------
if(NOT DEFINED ENABLE_SIMPLE_EXAMPLE)
    set(ENABLE_SIMPLE_EXAMPLE TRUE CACHE BOOL "Enable to make simple example")
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples AND ENABLE_SIMPLE_EXAMPLE) 
	# probably there's a simpler way to link against multiple executables...
		add_executable(exampleSimple examples/exampleSimple.cpp)
	target_link_libraries(exampleSimple ${the_library} opencv_core opencv_imgproc opencv_highgui )
endif()

#---------------------------------
# add examples
#---------------------------------
if(NOT DEFINED ENABLE_SAMPLES)
    set(ENABLE_SAMPLES FALSE CACHE BOOL "Enable to make the samples")
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples AND ENABLE_SAMPLES) 
	# probably there's a simpler way to link against multiple executables...
	add_executable(exampleTest examples/exampleTest.cpp)
	target_link_libraries(exampleTest ${the_library} opencv_core opencv_imgproc opencv_highgui )

	add_executable(exampleUpdate examples/exampleUpdate.cpp)
	target_link_libraries(exampleUpdate ${the_library} opencv_core opencv_imgproc opencv_highgui)

	add_executable(exampleWebCam examples/exampleWebCam.cpp)
	target_link_libraries(exampleWebCam ${the_library} opencv_core opencv_imgproc opencv_highgui opencv_objdetect)
endif()