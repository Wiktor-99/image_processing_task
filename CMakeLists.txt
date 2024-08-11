cmake_minimum_required(VERSION 3.22)
project(image_processing_app CXX)

set(LOADPNG lodepng)
include(FetchContent)
FetchContent_Declare(
  ${LOADPNG}
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG master
)
FetchContent_MakeAvailable(lodepng)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(image_processing/src)
add_subdirectory(tests)
add_library(lodepng STATIC
  ${lodepng_SOURCE_DIR}/lodepng.cpp
  ${lodepng_SOURCE_DIR}/lodepng.h
)
add_executable(
  image_processing_app
  src/main.cpp
  src/image_processing_app.cpp
)
target_compile_features(image_processing_app PUBLIC cxx_std_20)

target_include_directories(image_processing_app PRIVATE ${lodepng_SOURCE_DIR} include)
target_link_libraries(
  image_processing_app
  lodepng
  image_processinglib
)
