#pragma once

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


    Vector() {}

    Vector(double x, double y, double z) :
            x(x),
            y(y),
            z(z) {}

    Vector(Point beg, Point end) {
        x = end.x - beg.x;
        y = end.y - beg.y;
        z = end.z - beg.z;
    }

    double Len() const;

    Vector Norm() const;

    Vector Mult(double k) const;

    static double DotProd(const Vector &l, const Vector &r);

    Vector Sum(const Vector &vec) const;

    Vector Reflect(Vector normal) const;
};


class Material {
public:
    double difAlbedo;
    double specAlbedo;
    double specular;
    double refl;

    Material() {}

    Material(double difAlbedo, double specAlbedo, double specular, double refl) :
            difAlbedo(difAlbedo),
            specAlbedo(specular),
            specular(specular),
            refl(refl) {}

};

class Sphere {
public:
    Point o;
    double r;
    Color color;
    Material mat;

    Sphere() {}

    Sphere(Point o, double r, Color color, Material mat) :
            color(color),
            o(o),
            r(r),
            mat(mat) {}

    double intersection(Point &camera, Point &p) const;
};