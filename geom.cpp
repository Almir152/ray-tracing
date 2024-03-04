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




