# image-lib
Simple/Clean Image Lib

1. Started out with a simple image class that mocked the image class in the project.
2. Then I added a simple grayscale example.
3. Then I added a CMake build system.
4. Added an image class that uses libjpeg to load and save images. (Installation https://github.com/libjpeg-turbo/libjpeg-turbo/releases)

# Done
- [x] Basic image class
- [x] Grayscale example
- [x] CMake build system

# Todo
- [ ] Load actual image files for testing
- [ ] Add code for time tracking


# Compile the library
<!-- cmake --build .  -->
cd build; cmake --build . --target clean; cd .. ; 
Remove-Item ".\build" -Recurse -Force
Get-ChildItem -Path . -Recurse -Filter "CMakeCache.txt" | Remove-Item -Force

cmake -Bbuild -S.
cmake --build build
cmake --trace-expand

cmake -D CUDA_TOOLKIT_ROOT_DIR="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.4" -Bbuild -S.
# Run the examples
rm grayscale_image.jpeg
.\build\Debug\grayscale_example.exe image.jpeg5r
