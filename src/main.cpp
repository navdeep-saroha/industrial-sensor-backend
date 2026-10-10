#include <iostream>
#include <vector>
#include <stdexcept>

//struct for storing all three co-ordinates in single object
struct Point3D {
    double x;
    double y;
    double z;
};
//struct that defines min and max co-ordinates
struct Bounds {
    Point3D min;
    Point3D max;
};
// calculates the min and max co-ordinates
Bounds compute_bounds(const std::vector<Point3D>& points){
    if(points.empty()){
        throw std::invalid_argument("compute_bounds: no points provided");
    }
    Bounds b{points[0], points[0]};
    for (const Point3D &point : points)
    {
        if (point.x < b.min.x)
        {
            b.min.x = point.x;
        }
        if(point.x > b.max.x){
            b.max.x = point.x;
        }
        if (point.y < b.min.y){
            b.min.y = point.y;
        }
        if(point.y > b.max.y){
            b.max.y = point.y;
        }

        if(point.z < b.min.z){
            b.min.z = point.z;
        }
        if(point.z > b.max.z){
            b.max.z = point.z;
        }
    }
    return b;
}
// calcualtes the total box dimension
// doesn't work if bounds are manually input with min > max
Point3D box_dimension(const Bounds&  b){
    return { b.max.x - b.min.x, b.max.y - b.min.y, b.max.z - b.min.z};
}
// calculate the centroid
Point3D compute_average(const std::vector<Point3D>& points){
    if (points.empty())
    {
        throw std::invalid_argument("compute_bounds: no points provided");
    }
    const double total_points = static_cast<double>(points.size());
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_z = 0.0;
    for(const Point3D& point: points){
        sum_x += point.x;
        sum_y += point.y;
        sum_z += point.z;
    }

    return {sum_x/total_points, sum_y/total_points, sum_z/total_points};
}

int main() {

    try{
        std::vector<Point3D> points{
            {12.4, 4.2, 103.5},
            {6.7, 6.9, 50.0},
            {10.0, 5.0, 80.0}};
        points.push_back({1.0, 2.0, 3.0});
        points.push_back({2.0, 3.0, 4.0});
        std::cout << "Number of points: " << points.size() << std::endl;

        for (const Point3D& point : points)
        {
            std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
        }
        Bounds b = compute_bounds(points); //calculates the min and max co-ordinates
        Point3D result = box_dimension(b); //total dimension
        std::vector<Point3D> empty_points{};
        Point3D centroid = compute_average(points);
        std::cout << "Box Dimensions: (" << result.x << ", " << result.y << ", " << result.z << ")" << std::endl;
        std::cout << "Box Centroid: (" << centroid.x << ", " << centroid.y << ", " << centroid.z << ")" << std::endl;

        return 0;
    }

    catch(const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
 }
