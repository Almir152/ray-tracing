#include "geom.h"

double Vector::DotProd(const Vector &l, const Vector &r) {
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

double Vector::Len() const {
    return sqrt(DotProd(*this, *this));
}

Vector Vector::Norm() const {
    double lengh = (*this).Len();
    return {x / lengh, y / lengh, z / lengh};
}

Vector Vector::Mult(double k) const {
    return {x * k, y * k, z * k};
}

Vector Vector::Sum(const Vector &vec) const {
    return {x + vec.x, y + vec.y, z + vec.z};
}

Vector Vector::Reflect(Vector norm) const {
    Vector Nb = norm.Norm().Mult(-DotProd((*this).Mult(-1), norm.Norm()));
    Vector Na = (*this).Sum(Nb.Mult(-1));
    return {Na.Sum(Nb.Mult(-1))};
}


double Sphere::intersection(Point &camera, Point &p) const {
    Sphere sphere = *this;
    Vector u = {sphere.o, camera};
    Vector v = {camera, p};

    double vv = Vector::DotProd(v, v);
    double uu = Vector::DotProd(u, u);
    double vu = Vector::DotProd(v, u);

    double disc = vu * vu - vv * (uu - sphere.r * sphere.r);
    if (disc < 0) {
        return 1e9;
    }

    double k1 = (-vu + sqrt(disc)) / vv;
    double k2 = (-vu - sqrt(disc)) / vv;
    double k = min(k1, k2);
    return k;
}
