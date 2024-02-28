#include <cmath>
#include "out.h"

using namespace std;


class Point {
public:
    double x;
    double y;
    double z;

    Point() {}

    Point(double x, double y, double z) : x(x), y(y), z(z) {}

};

class Vector {
public:
    double x;
    double y;
    double z;
    double len;


    Vector() {}

    Vector(double x, double y, double z) :
            x(x),
            y(y),
            z(z),
            len(sqrt(x * x + y * y + z * z)) {}

    Vector(Point beg, Point end) {
        x = end.x - beg.x;
        y = end.y - beg.y;
        z = end.z - beg.z;
        len = sqrt(x * x + y * y + z * z);
    }
};

double DotProd(Vector &l, Vector &r);

Vector Norm(Vector v);

class Sphere {
public:
    Point o;
    double r;
    Color color;

    Sphere() {}

    Sphere(Point o, double r, Color color) :
            o(o),
            r(r),
            color(color) {}
};