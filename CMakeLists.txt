cmake_minimum_required(VERSION 3.15)
project(ImageLibrary VERSION 1.0.0 LANGUAGES CXX CUDA)
cmake_policy(SET CMP0146 NEW)


# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)
set(CUDA_TOOLKIT_ROOT_DIR "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v12.4")

# Find CUDA and set up the CUDA toolkit
# find_package(CUDA REQUIRED)
enable_language(CUDA)
find_package(CUDAToolkit REQUIRED)

set(CMAKE_CUDA_ARCHITECTURES 75 86)

# List the C++ and CUDA source files separately
set(CXX_SOURCES
    src/image.cpp
    src/processing.cpp
)

set(CUDA_SOURCES
    src/processing_cu.cu  # Add your .cu files here
)

# Library setup for C++ and CUDA
add_library(image_library STATIC
    ${CXX_SOURCES}
    ${CUDA_SOURCES}  # Link CUDA sources to the library
)

# Specify CUDA specific compilation flags if needed
set_target_properties(image_library PROPERTIES
    CUDA_RESOLVE_DEVICE_SYMBOLS ON
    CUDA_SEPARABLE_COMPILATION ON  # Allow CUDA to compile separately
)

# Include directories for the library
target_include_directories(image_library PUBLIC 
    ${CMAKE_SOURCE_DIR}/include  # Link your project's include directory
)

# Link CUDA libraries to image_library
target_link_libraries(image_library PRIVATE CUDA::cudart)  # Link with CUDA runtime

# Example setup (compile and link examples)
file(GLOB EXAMPLE_SOURCES examples/*.cpp)
foreach(example_source ${EXAMPLE_SOURCES})
    get_filename_component(example_name ${example_source} NAME_WE)
    add_executable(${example_name} ${example_source})
    
    # Link the image_library to each example
    target_link_libraries(${example_name} PRIVATE image_library)
endforeach()



# Example setup (compile and link examples)
file(GLOB EXAMPLE_SOURCES examples/*.cu)
foreach(example_source ${EXAMPLE_SOURCES})
    get_filename_component(example_name ${example_source} NAME_WE)
    add_executable(${example_name} ${example_source})
    
    # Link the image_library to each example
    target_link_libraries(${example_name} PRIVATE image_library)
endforeach()
