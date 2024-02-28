#include "geom.h"


double DotProd(Vector &l, Vector &r) {
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

Vector Norm(Vector v) {
    return Vector(v.x / v.len, v.y / v.len, v.z / v.len);
}