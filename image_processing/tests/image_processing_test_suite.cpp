#include "image_processing.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <ranges>

using namespace testing;
namespace
{
constexpr double RED_FACTOR{0.299};
constexpr double GREEN_FACTOR{0.587};
constexpr double BLUE_FACTOR{0.114};
}

namespace image_processing
{

MATCHER_P(ImagMatcher, expected, "")
{
  return std::ranges::equal(expected, arg, [](const auto& lhs, const auto& rhs)
  {
    return std::ranges::equal(lhs, rhs);
  });
}

TEST(RgbToGrayScaleTest, GivenEmptyRGBImageShouldReturnEmptyGrayscaleImage)
{
  const RgbImage inputImage{};
  EXPECT_TRUE(rgbToGrayScale(inputImage).empty());
}

TEST(RgbToGrayScaleTest, GivenRGBImageWithOnePixelShouldReturnOnePixelGrayscaleImageWhichIsSumOfWeightedRGBValues)
{
  const PixelRGB pixel{ .r = std::byte{90}, .g = std::byte{90} , .b = std::byte{90}};
  const RgbImage inputImage{{pixel}};
  const GrayScaleImage outputImage{ {
    static_cast<std::byte>(
      std::to_integer<int>(pixel.r) * RED_FACTOR +
      std::to_integer<int>(pixel.g) * GREEN_FACTOR +
      std::to_integer<int>(pixel.b) * BLUE_FACTOR) } };

  EXPECT_THAT(rgbToGrayScale(inputImage), ImagMatcher(outputImage));
}

};