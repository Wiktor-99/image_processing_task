#include "image_processing_app.hpp"

namespace image_processing_app
{
image_processing::RgbImage createRGBImageFromVectorOfBytes(
  const std::vector<unsigned char>& image, unsigned height, unsigned width)
{
  image_processing::RgbImage imageRgb;
  for (std::size_t y = 0; y < height; ++y)
  {
    std::vector<image_processing::PixelRGB> row;
    for (std::size_t x = 0; x < width; ++x)
    {
      const std::size_t indexOfRedColor{RGB_STEP * (width * y + x)};
      row.emplace_back(image_processing::PixelRGB{
        .r = std::byte{image[indexOfRedColor]},
        .g = std::byte{image[indexOfRedColor + OFFSET_TO_GREEN]},
        .b = std::byte{image[indexOfRedColor + OFFSET_TO_BLUE]}});
    }
    imageRgb.push_back(row);
  }
  return imageRgb;
}

std::vector<unsigned char> grayscaleImageToVectorOfBytes(const image_processing::GrayScaleImage& grayImage)
{
  std::vector<unsigned char> outputImage;
  outputImage.reserve(grayImage.front().size() * grayImage.size());
  for (const auto& row : grayImage)
  {
    std::transform(
      row.begin(), row.end(), std::back_inserter(outputImage),
      [](const auto& grayPixel) { return static_cast<unsigned char>(grayPixel); });
  }
  return outputImage;
}

std::optional<std::filesystem::path> validateInputData(int argc, char* argv[])
{
  if (argc < EXPECTED_NUMBER_OF_ARGUMENTS)
  {
    std::cout << "Not enough arguments. Add following options -i path_to_png_image \n";
    return std::nullopt;
  }
  if (std::string(argv[INDEX_OF_INPUT_OPTION]) != "-i")
  {
    std::cout << "Wrong option for input file. Add following options -i path_to_png_image \n";
    return std::nullopt;
  }
  std::filesystem::path filePath{argv[INDEX_OF_PATH_TO_FILE]};
  if (filePath.extension() != ".png")
  {
    std::cout << "Provided file is not png image.\n";
    return std::nullopt;
  }
  return filePath;
}
};  // namespace image_processing_app