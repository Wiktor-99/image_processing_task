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
MATCHER_P(ImagMatcher, expected, "")
{
  return std::ranges::equal(expected, arg, [](const auto& lhs, const auto& rhs)
  {
    return std::ranges::equal(lhs, rhs);
  });
}
}

namespace image_processing
{

TEST(RgbToGrayScaleTest, GivenEmptyRGBImageShouldReturnEmptyGrayscaleImage)
{
  const RgbImage inputImage{};
  EXPECT_TRUE(rgbToGrayScale(inputImage).empty());
}

TEST(RgbToGrayScaleTest, GivenRGBImageWithOnePixelShouldReturnOnePixelGrayscaleImageWhichIsSumOfWeightedRGBValues)
{
  const PixelRGB pixel{ .r = std::byte{90}, .g = std::byte{90}, .b = std::byte{90} };
  const RgbImage inputImage{{pixel}};
  const GrayScaleImage outputImage{ {
    static_cast<std::byte>(
      std::to_integer<int>(pixel.r) * RED_FACTOR +
      std::to_integer<int>(pixel.g) * GREEN_FACTOR +
      std::to_integer<int>(pixel.b) * BLUE_FACTOR) } };

  EXPECT_THAT(rgbToGrayScale(inputImage), ImagMatcher(outputImage));
}

TEST(RgbToGrayScaleTest, GivenRGBImageShouldReturnOneGrayscaleImageWhichIsSumOfWeightedRGBValues)
{
  const PixelRGB firstPixel{ .r = std::byte{90}, .g = std::byte{90}, .b = std::byte{90} };
  const PixelRGB secondTwo{ .r = std::byte{190}, .g = std::byte{90}, .b = std::byte{90} };
  const PixelRGB thirdThree{ .r = std::byte{90}, .g = std::byte{90}, .b = std::byte{190} };
  const PixelRGB fourthPixel{ .r = std::byte{90}, .g = std::byte{190}, .b = std::byte{90} };
  const RgbImage inputImage
  {
    {firstPixel, secondTwo},
    {thirdThree, fourthPixel},
  };
  const GrayScaleImage outputImage
  {
    {
      static_cast<std::byte>(
        std::to_integer<int>(firstPixel.r) * RED_FACTOR +
        std::to_integer<int>(firstPixel.g) * GREEN_FACTOR +
        std::to_integer<int>(firstPixel.b) * BLUE_FACTOR),
      static_cast<std::byte>(
        std::to_integer<int>(secondTwo.r) * RED_FACTOR +
        std::to_integer<int>(secondTwo.g) * GREEN_FACTOR +
        std::to_integer<int>(secondTwo.b) * BLUE_FACTOR)
    },
    {
      static_cast<std::byte>(
        std::to_integer<int>(thirdThree.r) * RED_FACTOR +
        std::to_integer<int>(thirdThree.g) * GREEN_FACTOR +
        std::to_integer<int>(thirdThree.b) * BLUE_FACTOR),
      static_cast<std::byte>(
        std::to_integer<int>(fourthPixel.r) * RED_FACTOR +
        std::to_integer<int>(fourthPixel.g) * GREEN_FACTOR +
        std::to_integer<int>(fourthPixel.b) * BLUE_FACTOR)
    }
  };

  EXPECT_THAT(rgbToGrayScale(inputImage), ImagMatcher(outputImage));
}

};