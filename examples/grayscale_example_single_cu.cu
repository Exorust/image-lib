#include <cuda_runtime.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "image_library/image.hpp"
#include "image_library/processing_cu.h"
#include <chrono>

// Example testing the implementation
int main(int argc, char *argv[])
{
    long long int image_size = std::pow(2048, 1);
    image_library::Image img(2048, 2048);

    // Convert the image to grayscale using the CUDA implementation
    auto start = std::chrono::high_resolution_clock::now();
    image_library::convertToGrayscaleCuda(img);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    // Output the first few pixel values to verify the grayscale conversion
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Pixel " << i << ": "
                  << static_cast<int>(img.getPixelData()[i * 3]) << ", "
                  << static_cast<int>(img.getPixelData()[i * 3 + 1]) << ", "
                  << static_cast<int>(img.getPixelData()[i * 3 + 2]) << std::endl;
    }

    return 0;
}