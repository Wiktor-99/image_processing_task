#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "image_processing.hpp"
#include "image_processing_app.hpp"

using namespace testing;
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

}  // namespace image_processing_app