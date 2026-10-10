#include <iostream>
#include <vector>
#include <stdexcept>

struct Point3D {
    double x;
    double y;
    double z;
};

double min_x(const std::vector<Point3D>& points){
    if (points.empty()){
        throw std::invalid_argument("min_x: no points provided");
    }
    double smallest = points[0].x;

    for (const Point3D& point : points){
        if (point.x < smallest) {
            smallest = point.x;
        }
    }

    return smallest;
}
double max_x(const std::vector<Point3D> &points)
{
    if (points.empty()){
        throw std::invalid_argument("max_x: no points provided");
    }
    double max = points[0].x;

    for (const Point3D &point : points)
    {
        if (point.x > max)
        {
            max = point.x;
        }
    }

    return max;
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
        std::cout << "Min x: " << min_x(points) << std::endl;
        std::cout << "Max x: " << max_x(points) << std::endl;
        return 0;
    }

    catch(const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
 }
