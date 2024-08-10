#include "image_processing.hpp"

namespace image_processing
{
constexpr double RED_FACTOR{0.299};
constexpr double GREEN_FACTOR{0.587};
constexpr double BLUE_FACTOR{0.114};

GrayScaleImage rgbToGrayScale(const RgbImage& image)
{
  GrayScaleImage result{};
  for (const auto& row : image)
  {
    std::vector<std::byte> output_row{};
    for (const auto& [r, g, b] : row)
    {
      output_row.emplace_back(static_cast<std::byte>(
        std::to_integer<int>(r) * RED_FACTOR + std::to_integer<int>(g) * GREEN_FACTOR +
        std::to_integer<int>(b) * BLUE_FACTOR));
    }
    result.emplace_back(output_row);
  }
  return result;
}
}  // namespace image_processing
