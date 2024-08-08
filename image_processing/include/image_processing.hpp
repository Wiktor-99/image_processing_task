#pragma once

#include <vector>
#include <cstddef>

namespace image_processing
{
struct PixelRGB;
using RgbImage = std::vector<std::vector<PixelRGB>>;
using GrayScaleImage = std::vector<std::vector<std::byte>>;

GrayScaleImage rgbToGrayScale(const RgbImage& image);

}
