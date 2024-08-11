#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include "image_processing.hpp"
#include "image_processing_app.hpp"
#include "lodepng.h"

constexpr int FAILURE{-1};

int main(int argc, char* argv[])
{
  const auto filePath{image_processing_app::validateInputData(argc, argv)};
  if (not filePath)
  {
    return FAILURE;
  }

  std::vector<unsigned char> image;
  unsigned width{}, height{};
  unsigned error = lodepng::decode(image, width, height, *filePath, LCT_RGB);
  if (error)
  {
    std::cout << std::format("Error while decoding png {} : {} \n", error, lodepng_error_text(error));
    return FAILURE;
  }
  const auto grayImage{
    image_processing::rgbToGrayScale(image_processing_app::createRGBImageFromVectorOfBytes(image, height, width))};
  error = lodepng::encode(
    "output.png", image_processing_app::grayscaleImageToVectorOfBytes(grayImage), width, height, LCT_GREY);
  if (error)
  {
    std::cout << std::format("Error while encoding png {} : {} \n", error, lodepng_error_text(error));
    return FAILURE;
  }
}