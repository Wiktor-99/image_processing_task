add_library(image_processinglib STATIC image_processing.cpp)
target_include_directories(image_processinglib PUBLIC  "../include")
target_compile_features(image_processinglib PUBLIC cxx_std_20)