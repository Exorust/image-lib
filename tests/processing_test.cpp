#include <gtest/gtest.h>
#include "image_library/image.hpp"
#include "image_library/processing.hpp"

TEST(ProcessingTest, ConvertToGrayscale)
{
    image_library::Image img(2, 2);
    auto &pixels = img.getPixelData();
    pixels = {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 255}; // R, G, B values

    image_library::convertToGrayscale(img);

    auto &processedPixels = img.getPixelData();
    ASSERT_EQ(processedPixels[0], 76);  // Grayscale for (255, 0, 0)
    ASSERT_EQ(processedPixels[3], 150); // Grayscale for (0, 255, 0)
    ASSERT_EQ(processedPixels[6], 29);  // Grayscale for (0, 0, 255)
    ASSERT_EQ(processedPixels[9], 255); // Grayscale for (255, 255, 255)
}
