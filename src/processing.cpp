#include "image_library/processing.hpp"
#include <cmath>

namespace image_library
{

    void convertToGrayscale(Image &img)
    {
        auto &pixelData = img.getPixelData();
        int width = img.getWidth();
        int height = img.getHeight();

        for (int i = 0; i < width * height; ++i)
        {
            int r = pixelData[i * 3 + 0];
            int g = pixelData[i * 3 + 1];
            int b = pixelData[i * 3 + 2];
            uint8_t grayscale = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
            pixelData[i * 3 + 0] = grayscale;
            pixelData[i * 3 + 1] = grayscale;
            pixelData[i * 3 + 2] = grayscale;
        }
    }

} // namespace image_library
