#pragma once
#include <vector>

struct Point3D {
    double x;
    double y;
    double z;
};

struct Bounds {
    Point3D min;
    Point3D max;
};

bool is_valid_point(const Point3D& point);
std::vector<Point3D> filter_valid_points(const std::vector<Point3D>& points);
Bounds compute_bounds(const std::vector<Point3D>& points);
Point3D box_dimension(const Bounds& b);
Point3D compute_average(const std::vector<Point3D>& points);