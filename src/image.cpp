#include "image_library/image.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace image_library
{
    // Default constructor
    Image::Image()
        : width(0), height(0), isDataLoaded(false)
    {
        // No pixel data loaded by default
        pixelData.clear();
    }

    // Constructor to create a mock image
    Image::Image(long long int width, long long int height)
        : width(width), height(height), isDataLoaded(true)
    {
        if (width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Width and height must be positive integers.");
        }

        // Reserve space for pixel data
        pixelData.resize(width * height * 3);

        // Mock pattern: alternating color bands
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                int index = (i * width + j) * 3;
                pixelData[index] = (i % 2 == 0) ? 255 : 0;     // Red channel
                pixelData[index + 1] = (j % 2 == 0) ? 255 : 0; // Green channel
                pixelData[index + 2] = 128;                    // Blue channel (constant)
            }
        }
    }

    // Constructor to load from a file
    Image::Image(const std::string &filepath)
        : width(0), height(0), sourceFile(filepath), isDataLoaded(false)
    {
        // The actual pixel data will be lazily loaded
    }

    // Save image to a file
    bool Image::save(const std::string &filepath) const
    {
        return savePixelData(filepath);
    }

    // Get width
    long long int Image::getWidth() const
    {
        return width;
    }

    // Get height
    long long int Image::getHeight() const
    {
        return height;
    }

    // Check if the image is valid
    bool Image::isValid() const
    {
        return width > 0 && height > 0 && isDataLoaded;
    }

    // Get mutable pixel data
    std::vector<uint8_t> &Image::getPixelData()
    {
        if (!isDataLoaded)
        {
            loadPixelData();
        }
        return pixelData;
    }

    // Get immutable pixel data
    const std::vector<uint8_t> &Image::getPixelData() const
    {
        if (!isDataLoaded)
        {
            loadPixelData();
        }
        return pixelData;
    }

    // Load pixel data from file (lazy loading)
    void Image::loadPixelData() const
    {
        if (!isDataLoaded)
        {
            // Mock implementation of file loading
        }
    }

    // Save pixel data to file
    bool Image::savePixelData(const std::string &filepath) const
    {
        std::ofstream file(filepath, std::ios::binary);
        if (!file)
        {
            return false;
        }

        // Mock BMP-like format (no headers for simplicity)
        file.write(reinterpret_cast<const char *>(pixelData.data()), pixelData.size());
        return file.good();
    }

} // namespace image_library
