#include <iostream>

struct Point3D {
    double x;
    double y;
    double z;
};

int main() {
    Point3D p{12.4, 4.2, 103.5};
    Point3D q{6.7, 6.9, 50.0};
    std::cout << "Point p: (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    std::cout << "Point q: (" << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
    return 0;
 }
