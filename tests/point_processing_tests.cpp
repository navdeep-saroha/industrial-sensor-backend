#include <gtest/gtest.h>
#include <limits>
#include "point_processing.h"
#include <stdexcept>

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

TEST(ComputeBoundsTest, ThrowsOnEmptyInput){
    std::vector<Point3D> empty_points = {};
    EXPECT_THROW(compute_bounds(empty_points), std::invalid_argument);
}

TEST(ComputeBoundsTest, SinglePointInput)
{
    std::vector<Point3D> single_point = {{1,2,3}};
    Bounds b = compute_bounds(single_point);
    EXPECT_DOUBLE_EQ(b.min.x, 1);
    EXPECT_DOUBLE_EQ(b.min.y, 2);
    EXPECT_DOUBLE_EQ(b.min.z, 3);
    EXPECT_DOUBLE_EQ(b.max.x, 1);
    EXPECT_DOUBLE_EQ(b.max.y, 2);
    EXPECT_DOUBLE_EQ(b.max.z, 3);
}

TEST(FilterValidPointTest, RemovesNanPoints){
   double nan1 = std::numeric_limits<double>::quiet_NaN();
   std::vector<Point3D> one_invalid_point = {
    {nan1, 2, 4},
    {1,2,3},
    {2,3,4},
   };
   std::vector<Point3D> result = filter_valid_points(one_invalid_point);
   ASSERT_EQ(result.size(), 2u);
   EXPECT_DOUBLE_EQ(result[0].x, 1.0);
   EXPECT_DOUBLE_EQ(result[1].x, 2.0);
}

TEST(ComputeAvgTest, FindCentroid){
    std::vector<Point3D> points = {
        {1,2,3},
        {4,5,6},
    };
    Point3D centroid = compute_average(points);
    EXPECT_DOUBLE_EQ(centroid.x, 2.5);
    EXPECT_DOUBLE_EQ(centroid.y, 3.5);
    EXPECT_DOUBLE_EQ(centroid.z, 4.5);
}