#include <iostream>
#include <vector>

struct Point3D {
    double x;
    double y;
    double z;
};

int main() {

    std::vector<Point3D> points{
        {12.4, 4.2, 103.5},
        {6.7, 6.9, 50.0},
        {10.0, 5.0, 80.0}
    };
    points.push_back({1.0, 2.0, 3.0});
    std::cout << "Number of points: " << points.size() << std::endl;

    for (const Point3D& point: points){
        std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << std::endl;
    }
    return 0;
 }
