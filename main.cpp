#include <bits/stdc++.h>
#include "geom.h"
#include "out.h"

using namespace std;


int const W = 1024;
int const H = 1024;

Point a = Point(0, 0, 0);

double const D = 1;

int main() {
    vector<vector<Pixel>> photo(W, vector<Pixel>(H, {0, 0, 0}));

    Point o = Point(0, 0, 5);
    double r = 1;
    double color_r = 0.4;
    double color_g = 0.6;
    double color_b = 0;
    Sphere s = Sphere(o, r, color_r, color_g, color_b);


    double x = -0.5;
    double y = 0.5;
    double z = D;
    for (int i = 0; i < H; i++) {
        x = -0.5;
        y -= i / H;
        for (int j = 0; j < W; j++) {
            x += j / 1024;
            Point p = Point(x, y, z);
            Vector v = Vector(a, p);
            Vector u = Vector(s.o, a);

            double vv = DotProd(v, v);
            double uu = DotProd(u, u);
            double vu = DotProd(v, u);

            double disc = vu * vu - vv * (uu - r * r);

            if (disc >= 0) {
                photo[i][j] = {s.color_r, s.color_g, s.color_b};
            }
        }
    }


    PrintPhoto(photo);
}