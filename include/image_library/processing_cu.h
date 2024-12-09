#ifndef IMAGE_LIBRARY_PROCESSING_H
#define IMAGE_LIBRARY_PROCESSING_H

#include "image.hpp"

namespace image_library
{

    // Convert the image to grayscale
    void convertToGrayscaleCuda(image_library::Image &img);

    // Convert the image to grayscale in parallel
    void convertToGrayscaleParallel(std::vector<image_library::Image> &images, int num_images);

} // namespace image_library

#endif // IMAGE_LIBRARY_PROCESSING_H
