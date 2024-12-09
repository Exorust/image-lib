#include "image_library/image.hpp"
#include "image_library/processing.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_image.png>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::string output_filename = "grayscale_" + input_filename;

    // Load the image
    // image_library::Image img(input_filename);
    long long int image_size = std::pow(2048, 1);
    image_library::Image img(image_size, image_size);
    if (!img.isValid())
    {
        std::cout << "Failed to load image: " << input_filename << std::endl;
        return 1;
    }

    // Convert to grayscale

    auto start = std::chrono::high_resolution_clock::now();
    image_library::convertToGrayscale(img);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    // Save the result
    if (!img.save(output_filename))
    {
        std::cout << "Failed to save image: " << output_filename << std::endl;
        return 1;
    }

    // Output the first few pixel values to verify the grayscale conversion
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Pixel " << i << ": "
                  << static_cast<int>(img.getPixelData()[i * 3]) << ", "
                  << static_cast<int>(img.getPixelData()[i * 3 + 1]) << ", "
                  << static_cast<int>(img.getPixelData()[i * 3 + 2]) << std::endl;
    }

    std::cout << "Successfully converted image to grayscale and saved as: " << output_filename << std::endl;
    return 0;
}
