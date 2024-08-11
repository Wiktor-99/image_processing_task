#include "gtest/gtest.h"
#include "image_processing.hpp"
#include "image_processing_app.hpp"

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

}  // namespace image_processing_app