cmake_minimum_required(VERSION 3.10)

project( DisplayImage )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( crangc crangc.cc )
target_link_libraries( crangc ${OpenCV_LIBS} )
