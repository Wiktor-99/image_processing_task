#pragma once

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

#include "image_processing.hpp"

namespace image_processing_app
{
image_processing::RgbImage createRGBImageFromVectorOfBytes(
  const std::vector<unsigned char>& image, unsigned height, unsigned width);

std::vector<unsigned char> grayscaleImageToVectorOfBytes(const image_processing::GrayScaleImage& grayImage);

std::optional<std::filesystem::path> validateInputData(int argc, char* argv[]);
};  // namespace image_processing_app