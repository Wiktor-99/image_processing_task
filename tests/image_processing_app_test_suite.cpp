#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "image_processing.hpp"
#include "image_processing_app.hpp"

using namespace testing;
using ImageWidth = unsigned;
using ImageHeight = unsigned;
namespace image_processing_app
{

TEST(ValidateInputDataTest, WhenGivenIsVectorWithSizeLessThenThreeShouldReturnNullopt)
{
  EXPECT_EQ(validateInputData({}), std::nullopt);
}

TEST(ValidateInputDataTest, WhenGivenIsVectorWithSecondElementOtherThenMinusIShouldReturnNullopt)
{
  EXPECT_EQ(validateInputData({"app", "-o"}), std::nullopt);
}

TEST(ValidateInputDataTest, WhenGivenIsVectorWithPathToFileWithExtensionDifferentThenPngShouldReturnNullopt)
{
  EXPECT_EQ(validateInputData({"app", "-i", "image.jpeg"}), std::nullopt);
}

TEST(ValidateInputDataTest, WhenGivenIsVectorContainsMinusIOptionAndPngFileShouldReturnPathToFile)
{
  ASSERT_NE(validateInputData({"app", "-i", "test/image.png"}), std::nullopt);
  ASSERT_STREQ(validateInputData({"app", "-i", "test/image.png"})->c_str(), "test/image.png");
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputImageIsEmptyShouldReturnEmptyVector)
{
  EXPECT_TRUE(grayscaleImageToVectorOfBytes(image_processing::GrayScaleImage{}).empty());
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputImageContainsManyRowsShouldReturnFlatVectorOfBytesConsideringRowsOrder)
{
  EXPECT_THAT(
    grayscaleImageToVectorOfBytes(image_processing::GrayScaleImage{
      {std::byte{1}, std::byte{2}},
      {std::byte{3}, std::byte{4}},
    }),
    ElementsAreArray({1, 2, 3, 4}));
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputVectorDoseNotHaveThreeValuesForEachPixelThenShouldReturnEmptyImage)
{
  EXPECT_TRUE(createRGBImageFromVectorOfBytes(std::vector<unsigned char>{}, ImageHeight{1}, ImageWidth{1}).empty());
  EXPECT_TRUE(createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2}, ImageHeight{1}, ImageWidth{1}).empty());
  EXPECT_TRUE(
    createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2, 3}, ImageHeight{1}, ImageWidth{2}).empty());
  EXPECT_TRUE(
    createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2, 3}, ImageHeight{2}, ImageWidth{1}).empty());
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputVectorDoseHaveThreeValuesForOnePixelShouldReturnRGBImage)
{
  const auto rgbImage{
    createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2, 3}, ImageHeight{1}, ImageWidth{1})};
  EXPECT_FALSE(rgbImage.empty());
  EXPECT_EQ(rgbImage.front().at(0).r, std::byte{1});
  EXPECT_EQ(rgbImage.front().at(0).g, std::byte{2});
  EXPECT_EQ(rgbImage.front().at(0).b, std::byte{3});
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputVectorIsTwoPixelHightShouldReturnRGBImageWithTwoRows)
{
  const auto rgbImage{
    createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2, 3, 4, 5, 6}, ImageHeight{2}, ImageWidth{1})};
  EXPECT_EQ(rgbImage.at(0).at(0).r, std::byte{1});
  EXPECT_EQ(rgbImage.at(0).at(0).g, std::byte{2});
  EXPECT_EQ(rgbImage.at(0).at(0).b, std::byte{3});
  EXPECT_EQ(rgbImage.at(1).at(0).r, std::byte{4});
  EXPECT_EQ(rgbImage.at(1).at(0).g, std::byte{5});
  EXPECT_EQ(rgbImage.at(1).at(0).b, std::byte{6});
}

TEST(GrayscaleImageToVectorOfBytesTest, WhenInputVectorIsTwoPixelWidthShouldReturnRGBImageWithTwoColumns)
{
  const auto rgbImage{
    createRGBImageFromVectorOfBytes(std::vector<unsigned char>{1, 2, 3, 4, 5, 6}, ImageHeight{1}, ImageWidth{2})};
  EXPECT_EQ(rgbImage.at(0).at(0).r, std::byte{1});
  EXPECT_EQ(rgbImage.at(0).at(0).g, std::byte{2});
  EXPECT_EQ(rgbImage.at(0).at(0).b, std::byte{3});
  EXPECT_EQ(rgbImage.at(0).at(1).r, std::byte{4});
  EXPECT_EQ(rgbImage.at(0).at(1).g, std::byte{5});
  EXPECT_EQ(rgbImage.at(0).at(1).b, std::byte{6});
}

TEST(
  GrayscaleImageToVectorOfBytesTest, WhenInputVectorIsTwoPixelWidthAndHightShouldReturnRGBImageWithTwoColumnsAndTwoRow)
{
  const auto rgbImage{createRGBImageFromVectorOfBytes(
    std::vector<unsigned char>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, ImageHeight{2}, ImageWidth{2})};
  EXPECT_EQ(rgbImage.at(0).at(0).r, std::byte{1});
  EXPECT_EQ(rgbImage.at(0).at(0).g, std::byte{2});
  EXPECT_EQ(rgbImage.at(0).at(0).b, std::byte{3});
  EXPECT_EQ(rgbImage.at(0).at(1).r, std::byte{4});
  EXPECT_EQ(rgbImage.at(0).at(1).g, std::byte{5});
  EXPECT_EQ(rgbImage.at(0).at(1).b, std::byte{6});
  EXPECT_EQ(rgbImage.at(1).at(0).r, std::byte{7});
  EXPECT_EQ(rgbImage.at(1).at(0).g, std::byte{8});
  EXPECT_EQ(rgbImage.at(1).at(0).b, std::byte{9});
  EXPECT_EQ(rgbImage.at(1).at(1).r, std::byte{10});
  EXPECT_EQ(rgbImage.at(1).at(1).g, std::byte{11});
  EXPECT_EQ(rgbImage.at(1).at(1).b, std::byte{12});
}

}  // namespace image_processing_app