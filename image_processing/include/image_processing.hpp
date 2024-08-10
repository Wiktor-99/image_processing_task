#pragma once

#include <cstddef>
#include <vector>

namespace image_processing
{
struct PixelRGB
{
  std::byte r{};
  std::byte g{};
  std::byte b{};
};
using RgbImage = std::vector<std::vector<PixelRGB>>;
using GrayScaleImage = std::vector<std::vector<std::byte>>;

GrayScaleImage rgbToGrayScale(const RgbImage& image);

}  // namespace image_processing
