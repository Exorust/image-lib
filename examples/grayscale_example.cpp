#include "image_library/image.hpp"
#include "image_library/processing.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_image_basename>" << std::endl;
        return 1;
    }

    std::string input_basename = argv[1];
    std::string output_basename = "grayscale_";

    const int num_images = 64;
    const long long int image_size = std::pow(2048, 1); // 2048x2048 image size

    // Array of images
    std::vector<image_library::Image> images(num_images);

    // Load all images
    for (int i = 0; i < num_images; ++i)
    {
        std::string input_filename = input_basename + "_" + std::to_string(i) + ".png";
        images[i] = image_library::Image(image_size, image_size);

        if (!images[i].isValid())
        {
            std::cout << "Failed to load image: " << input_filename << std::endl;
            return 1;
        }
    }

    // Convert all images to grayscale and measure processing time
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_images; ++i)
    {
        image_library::convertToGrayscale(images[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to process " << num_images << " images: " << duration.count() << " seconds" << std::endl;

    // Save all processed images
    for (int i = 0; i < num_images; ++i)
    {
        std::string output_filename = output_basename + std::to_string(i) + ".png";
        if (!images[i].save(output_filename))
        {
            std::cout << "Failed to save image: " << output_filename << std::endl;
            return 1;
        }
    }

    // Output the first few pixel values of the first image to verify grayscale conversion
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Pixel " << i << ": "
                  << static_cast<int>(images[0].getPixelData()[i * 3]) << ", "
                  << static_cast<int>(images[0].getPixelData()[i * 3 + 1]) << ", "
                  << static_cast<int>(images[0].getPixelData()[i * 3 + 2]) << std::endl;
    }

    std::cout << "Successfully converted all images to grayscale and saved with basename: " << output_basename << std::endl;
    return 0;
}
