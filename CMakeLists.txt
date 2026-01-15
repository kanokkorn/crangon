cmake_minimum_required(VERSION 3.14)

project(crangon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.13.0
)

FetchContent_Declare(
  opencv
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG        4.9.0
  CMAKE_ARGS     -DWITH_IPP=OFF -DWITH_ITT=OFF -DBUILD_IPP=OFF -DBUILD_ITT=OFF
)

FetchContent_Declare(
  sqlite3
  URL https://www.sqlite.org/2024/sqlite-amalgamation-3450000.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(spdlog opencv sqlite3)

add_library(sqlite INTERFACE)
target_sources(sqlite INTERFACE ${sqlite3_SOURCE_DIR}/sqlite3.c)
target_include_directories(sqlite INTERFACE ${sqlite3_SOURCE_DIR})

add_executable(crangon
  src/main.cc
  src/vision/crangc.cc
  src/database/sqldb.cc
  src/hw/hw_check.cc
)

target_include_directories(crangon PRIVATE
  "${PROJECT_SOURCE_DIR}/src"
  "${sqlite3_SOURCE_DIR}"
)

target_link_libraries(crangon PRIVATE
  spdlog::spdlog
  opencv_core
  opencv_imgproc
  opencv_highgui
  sqlite
)
