#include <cmath>

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

    Vector(double x, double y, double z) : x(x), y(y), z(z), len(sqrt(x * x + y * y + z * z)) {}

    Vector(Point beg, Point end) {
        x = end.x - beg.x;
        y = end.y - beg.y;
        z = end.z - beg.z;
        len = sqrt(x * x + y * y + z * z);
    }

    Vector operator+(Vector b){
        return Vector(x + b.x, y + b.y, z + b.z);
    }

    Vector operator-(Vector b){
        return Vector(x - b.x, y - b.y, z - b.z);
    }
};

double DotProd(Vector &l, Vector &r);

double CrossProd(Vector &l, Vector &r);

Vector Norm(Vector &v);

Vector MultVec(Vector &a, double k);


class Sphere {
public:
    Point o;
    double r;
    double color_r, color_g, color_b;

    Sphere() {}

    Sphere(Point o, double r, double color_r, double color_g, double color_b) :
            o(o),
            r(r),
            color_r(color_r),
            color_g(color_g),
            color_b(color_b) {}
};

class Triangle {
public:
    Point a;
    Point b;
    Point c;

    Triangle() {}

    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}
};

bool InTriangle(Triangle &t, Point &p);


class Screen {

};