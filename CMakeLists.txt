cmake_minimum_required(VERSION 3.10)

project( crangon )

find_package( OpenCV REQUIRED )
find_package( spdlog REQUIRED )

set (
    SOURCE_FILES
    src/crangc.cc
)

set (CMAKE_CXX_STANDARD 11)

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( crangc src/crangc.cc )
target_link_libraries(
    crangc 
    ${OpenCV_LIBS} 
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
  )
