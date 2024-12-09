#include <cuda_runtime.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "image_library/processing_cu.h"

namespace image_library
{
    // Kernel function for converting the image to grayscale
    __global__ void convertToGrayscaleKernel(uint8_t *pixelData, int width, int height)
    {
        int idx = blockIdx.x * blockDim.x + threadIdx.x;

        if (idx < width * height)
        {
            int r = pixelData[idx * 3 + 0];
            int g = pixelData[idx * 3 + 1];
            int b = pixelData[idx * 3 + 2];
            uint8_t grayscale = static_cast<uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
            pixelData[idx * 3 + 0] = grayscale;
            pixelData[idx * 3 + 1] = grayscale;
            pixelData[idx * 3 + 2] = grayscale;
        }
    }

    // Function to handle memory allocation and kernel launch
    void convertToGrayscaleCuda(Image &img)
    {
        int width = img.getWidth();
        int height = img.getHeight();
        auto &pixelData = img.getPixelData();
        printf("Run on Cuda\n");

        uint8_t *d_pixelData;
        size_t dataSize = width * height * 3 * sizeof(uint8_t);

        // Allocate device memory
        cudaMalloc(&d_pixelData, dataSize);

        // Copy pixel data to device
        cudaMemcpy(d_pixelData, pixelData.data(), dataSize, cudaMemcpyHostToDevice);

        // Launch kernel with sufficient threads
        int threadsPerBlock = 256;
        int blocksPerGrid = (width * height + threadsPerBlock - 1) / threadsPerBlock;
        convertToGrayscaleKernel<<<blocksPerGrid, threadsPerBlock>>>(d_pixelData, width, height);

        // Wait for the kernel to finish
        cudaDeviceSynchronize();

        // Copy the processed pixel data back to host
        cudaMemcpy(pixelData.data(), d_pixelData, dataSize, cudaMemcpyDeviceToHost);

        // Free device memory
        cudaFree(d_pixelData);
    }

    // CUDA kernel for converting image to grayscale
    __global__ void convertToGrayscaleKernelParallel(uint8_t *image_data, int width, int height, int num_images)
    {
        int idx = blockIdx.x * blockDim.x + threadIdx.x;
        if (idx < num_images * width * height)
        {
            int image_idx = idx / (width * height);
            int pixel_idx = idx % (width * height);
            int pixel_base = image_idx * width * height * 3 + pixel_idx * 3;

            uint8_t r = image_data[pixel_base];
            uint8_t g = image_data[pixel_base + 1];
            uint8_t b = image_data[pixel_base + 2];

            // Convert to grayscale using the average method
            uint8_t gray = static_cast<uint8_t>(0.2989f * r + 0.5870f * g + 0.1140f * b);

            // Store the grayscale value in place of the original RGB values
            image_data[pixel_base] = gray;
            image_data[pixel_base + 1] = gray;
            image_data[pixel_base + 2] = gray;
        }
    }

    // Host function to manage grayscale conversion for multiple images
    void convertToGrayscaleParallel(std::vector<image_library::Image> &images, int num_images)
    {
        int width = images[0].getWidth();
        int height = images[0].getHeight();
        size_t image_size = width * height * 3 * sizeof(uint8_t);

        // Allocate memory for image data on the device
        uint8_t *d_image_data;
        cudaMalloc(&d_image_data, num_images * image_size);

        // Copy image data from host to device
        for (int i = 0; i < num_images; ++i)
        {
            cudaMemcpy(d_image_data + i * width * height * 3, images[i].getPixelData().data(), image_size, cudaMemcpyHostToDevice);
        }

        // Launch kernel to process images in parallel
        int block_size = 256;
        int num_blocks = (num_images * width * height + block_size - 1) / block_size;
        convertToGrayscaleKernelParallel<<<num_blocks, block_size>>>(d_image_data, width, height, num_images);

        // Wait for kernel to finish
        cudaDeviceSynchronize();

        // Copy processed image data back to host
        for (int i = 0; i < num_images; ++i)
        {
            cudaMemcpy(images[i].getPixelData().data(), d_image_data + i * width * height * 3, image_size, cudaMemcpyDeviceToHost);
        }

        // Free device memory
        cudaFree(d_image_data);
    }

} // namespace image_library