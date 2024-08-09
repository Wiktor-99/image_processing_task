#include "image_processing.hpp"
#include "gtest/gtest.h"


TEST(RgbToGrayScaleTest, GivenEmptyRGBImageShouldReturnEmptyGrayscaleImage)
{
  const image_processing::RgbImage inputImage{};
  EXPECT_TRUE(image_processing::rgbToGrayScale(inputImage).empty());
}