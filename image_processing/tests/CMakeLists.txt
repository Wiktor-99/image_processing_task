include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(
  image_processing_test_suite
  image_processing_test_suite.cpp
)
target_link_libraries(
    image_processing_test_suite PRIVATE
    gtest_main
    gmock
    image_processinglib
)

target_compile_features(image_processing_test_suite PUBLIC cxx_std_20)
include(GoogleTest)
gtest_discover_tests(image_processing_test_suite)