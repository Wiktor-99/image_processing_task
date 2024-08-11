#pragma once

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

#include "image_processing.hpp"

constexpr std::size_t OFFSET_TO_GREEN{1};
constexpr std::size_t OFFSET_TO_BLUE{2};
constexpr std::size_t RGB_STEP{3};
constexpr std::size_t INDEX_OF_INPUT_OPTION{1};
constexpr std::size_t INDEX_OF_PATH_TO_FILE{2};
constexpr int EXPECTED_NUMBER_OF_ARGUMENTS{3};

namespace image_processing_app
{
image_processing::RgbImage createRGBImageFromVectorOfBytes(
  const std::vector<unsigned char>& image, unsigned height, unsigned width);

std::vector<unsigned char> grayscaleImageToVectorOfBytes(const image_processing::GrayScaleImage& grayImage);

std::optional<std::filesystem::path> validateInputData(int argc, char* argv[]);
};  // namespace image_processing_app