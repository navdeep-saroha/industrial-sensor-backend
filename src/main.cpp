#include <iostream>
#include <vector>
#include <stdexcept>

struct Point3D {
    double x;
    double y;
    double z;
};

struct Bounds {
    Point3D min;
    Point3D max;
};

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

int main() {

    try{
        std::vector<Point3D> points{
            {12.4, 4.2, 103.5},
            {6.7, 6.9, 50.0},
            {10.0, 5.0, 80.0}};
        points.push_back({1.0, 2.0, 3.0});
        std::cout << "Number of points: " << points.size() << std::endl;

        for (const Point3D &point : points)
        {
            std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
        }
        Bounds b = compute_bounds(points);
        std::cout << "Min: (" << b.min.x << ", " << b.min.y << ", " << b.min.z << ")" << std::endl;
        return 0;
    }

    catch(const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
 }
