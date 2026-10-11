#include <gtest/gtest.h>

#include "point_processing.h"


TEST(ComputeBoundsTest, FindMinAndMax){
    std::vector<Point3D> points = {
        {1.0, 5.0, 9.0},
        {4.0, 2.0, 6.0},
    };

    Bounds b = compute_bounds(points);
    EXPECT_DOUBLE_EQ(b.min.x, 1.0);
    EXPECT_DOUBLE_EQ(b.min.y, 2.0);
    EXPECT_DOUBLE_EQ(b.min.z, 6.0);
    EXPECT_DOUBLE_EQ(b.max.x, 4.0);
    EXPECT_DOUBLE_EQ(b.max.y, 5.0); 
    EXPECT_DOUBLE_EQ(b.max.z, 9.0);
}