#include "point_processing.h"


#include <cmath>
#include <stdexcept>

// check point for invalid values
bool is_valid_point(const Point3D &point)
{
    return std::isfinite(point.x) &&
           std::isfinite(point.y) &&
           std::isfinite(point.z);
}
// accept valid points but don't throw away whole batch
std::vector<Point3D> filter_valid_points(const std::vector<Point3D> &points)
{
    std::vector<Point3D> valid;
    for (const Point3D &point : points)
    {
        if (is_valid_point(point))
        {
            valid.push_back(point);
        }
    }
    if (valid.empty())
    {
        throw std::invalid_argument("no valid points provided");
    }
    return valid;
}

// calculates the min and max co-ordinates
Bounds compute_bounds(const std::vector<Point3D> &points)
{
    if (points.empty())
    {
        throw std::invalid_argument("compute_bounds: no points provided");
    }
    Bounds b{points[0], points[0]};
    for (const Point3D &point : points)
    {
        if (point.x < b.min.x)
        {
            b.min.x = point.x;
        }
        if (point.x > b.max.x)
        {
            b.max.x = point.x;
        }
        if (point.y < b.min.y)
        {
            b.min.y = point.y;
        }
        if (point.y > b.max.y)
        {
            b.max.y = point.y;
        }

        if (point.z < b.min.z)
        {
            b.min.z = point.z;
        }
        if (point.z > b.max.z)
        {
            b.max.z = point.z;
        }
    }
    return b;
}
// calcualtes the total box dimension
// doesn't work if bounds are manually input with min > max
Point3D box_dimension(const Bounds &b)
{
    return {b.max.x - b.min.x, b.max.y - b.min.y, b.max.z - b.min.z};
}
// calculate the centroid
Point3D compute_average(const std::vector<Point3D> &points)
{
    if (points.empty())
    {
        throw std::invalid_argument("compute_bounds: no points provided");
    }
    const double total_points = static_cast<double>(points.size());
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_z = 0.0;
    for (const Point3D &point : points)
    {
        sum_x += point.x;
        sum_y += point.y;
        sum_z += point.z;
    }

    return {sum_x / total_points, sum_y / total_points, sum_z / total_points};
}
