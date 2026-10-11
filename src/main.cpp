#include <iostream>
#include <limits>
#include "point_processing.h"


int main() {

    try{
        std::vector<Point3D> points{
            {12.4, 4.2, 103.5},
            {6.7, 6.9, 50.0},
            {10.0, 5.0, 80.0}};
        points.push_back({1.0, 2.0, 3.0});
        points.push_back({2.0, 3.0, 4.0});
        double nan1 = std::numeric_limits<double>::quiet_NaN();
        points.push_back({nan1, 2.0, 3.0});
        std::cout << "Number of points: " << points.size() << std::endl;
        std::vector<Point3D> valid_points = filter_valid_points(points);
        std::size_t rejected = points.size() - valid_points.size();

        std::cout << "Valid points: " << valid_points.size() << std::endl;
        std::cout << "Rejected points: " << rejected << std::endl;

        Bounds b = compute_bounds(valid_points);

        for (const Point3D& point : valid_points)
        {
            std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
        }
        Point3D result = box_dimension(b); //total dimension
        Point3D centroid = compute_average(valid_points);
        std::cout << "Box Dimensions: (" << result.x << ", " << result.y << ", " << result.z << ")" << std::endl;
        std::cout << "Centroid: (" << centroid.x << ", " << centroid.y << ", " << centroid.z << ")" << std::endl;



        return 0;
    }

    catch(const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
 }
