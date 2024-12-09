#include <gtest/gtest.h>
#include "image_library/image.hpp"

TEST(ImageTest, CreateImage)
{
    image_library::Image img(100, 100);
    ASSERT_EQ(img.getWidth(), 100);
    ASSERT_EQ(img.getHeight(), 100);
}
