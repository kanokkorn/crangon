cmake_minimum_required(VERSION 3.10)

project( crangon )

include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG        v1.13.0
  CMAKE_ARGS -DSPDLOG_FMT_EXTERNAL=ON
)

FetchContent_Declare(
  OpenCV
  GIT_REPOSITORY https://github.com/opencv/opencv
  GIT_TAG        dad8af6b17f8e60d7b95a1203a1b4d22f56574cf
  CMAKE_ARGS -DSPDLOG_FMT_EXTERNAL=ON
)

# if(NOT spdlog_POPULATED)
#   FetchContent_MakeAvailable(spdlog)
#   # Add spdlog as a subdirectory to make its targets available
#   add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
# endif()

find_package( OpenCV REQUIRED )
find_package( spdlog REQUIRED )

set (
    SOURCE_FILES
    src/crangc.cc
)

set (CMAKE_CXX_STANDARD 11)
set (BUILD_SHARED_LIBS OFF)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${spdlog_INCLUDE_DIRS} )
add_executable( crangc src/crangc.cc )
target_link_libraries(
    crangc
    ${OpenCV_LIBS} 
    spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
  )
