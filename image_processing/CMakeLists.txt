cmake_minimum_required(VERSION 3.22)
project(image_processing CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(image_processinglib src/image_processing.cpp)
target_compile_features(image_processinglib PUBLIC cxx_std_20)
target_include_directories(image_processinglib PUBLIC include)

enable_testing()
add_executable(
  image_processing_test_suite
  tests/image_processing_test_suite.cpp
)
target_link_libraries(
    image_processing_test_suite
    gtest_main
    image_processinglib
)
target_compile_features(image_processing_test_suite PUBLIC cxx_std_20)
include(GoogleTest)
gtest_discover_tests(image_processing_test_suite)