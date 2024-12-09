#ifndef IMAGE_LIBRARY_IMAGE_HPP
#define IMAGE_LIBRARY_IMAGE_HPP

#include <vector>
#include <string>
#include <cstdint>

namespace image_library
{
    class Image
    {
    public:
        // Default constructor
        Image();
        // Constructor to create a mock image
        Image(long long int width, long long int height);

        // Constructor to load from a file
        Image(const std::string &filepath);

        // Save image to a file
        bool save(const std::string &filepath) const;

        // Get image width
        long long int getWidth() const;

        // Get image height
        long long int getHeight() const;

        // Check if the image is valid
        bool isValid() const;

        // Get mutable pixel data
        std::vector<uint8_t> &getPixelData();

        // Get immutable pixel data
        const std::vector<uint8_t> &getPixelData() const;

    private:
        long long int width;            // Image width
        long long int height;           // Image height
        std::vector<uint8_t> pixelData; // Pixel data (RGB format)
        std::string sourceFile;         // Filepath for lazy loading
        mutable bool isDataLoaded;      // Flag indicating if pixel data is loaded

        // Load pixel data from file (lazy loading)
        void loadPixelData() const;

        // Save pixel data to file
        bool savePixelData(const std::string &filepath) const;
    };

} // namespace image_library

#endif // IMAGE_LIBRARY_IMAGE_HPP
