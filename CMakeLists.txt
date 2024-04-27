cmake_minimum_required(VERSION 3.10)

project( crangon )

find_package( OpenCV REQUIRED )

set (
    SOURCE_FILES
    src/crangc.cc
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( crangc src/crangc.cc )
target_link_libraries( crangc ${OpenCV_LIBS} )
