# tests/CMakeLists.txt

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Locate GoogleTest
find_package(GTest REQUIRED)

# Add test executables
add_executable(image_test image_test.cpp)
add_executable(processing_test processing_test.cpp)

# Link the test executables with GTest and the image_library
target_link_libraries(image_test PRIVATE GTest::GTest GTest::Main image_library)
target_link_libraries(processing_test PRIVATE GTest::GTest GTest::Main image_library)

# Register tests with CTest
add_test(NAME ImageTest COMMAND image_test)
add_test(NAME ProcessingTest COMMAND processing_test)
