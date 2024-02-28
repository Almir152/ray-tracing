#include <bits/stdc++.h>
#include "geom.h"

using namespace std;


int const W = 1024;
int const H = 1024;
double const D = W * sqrt(3) / 2;

double const SQH = H / D;
double const SQW = W / D;
double const SQD = 1;


Color const BG = {0.3, 0.3, 0.3};


class Light {
public:
    Point p;
    double power;

    Light() {}

    Light(Point p, double power) : p(p), power(power) {}
};


int main() {
    vector<vector<Color>> photo(H, vector<Color>(W, BG)); // картинка
    Point camera = Point(0, 0, 0); // позиция игрока

    // сферы:
    int sphereCol = 2;
    vector<Sphere> spheres = {
            //Sphere({-0.4, 0.6, 7}, 1, {0.3, 0.3, 0.3}),
            Sphere({0, 0, 5}, 1.5, {1, 0, 1})
    };

    // источники света:
    int lightCol = 1;
    vector<Light> lights = {
            Light({0, 10, 5}, 1),
            Light({10, 0, 5}, 1)
    };


    for (int i = 0; i < H; i++) {
        Point p = {-SQW / 2, SQH / 2 - (double(i) * SQH) / (H - 1), SQD};
        Color color_i_j;

        for (int j = 0; j < W; j++) {
            color_i_j = photo[i][j];
            double min_k = 1e9;
            Sphere drawn_sphere;
            bool isexist = 0;

            // проходим по всем сферам
            for (auto sphere: spheres) {
                Vector u = {sphere.o, camera};
                Vector v = {camera, p};

                double vv = DotProd(v, v);
                double uu = DotProd(u, u);
                double vu = DotProd(v, u);

                double disc = vu * vu - vv * (uu - sphere.r * sphere.r);
                if (disc < 0) {
                    continue;
                }
                isexist = 1;

                double k1 = (-vu + sqrt(disc)) / vv;
                double k2 = (-vu - sqrt(disc)) / vv;
                double k = min(k1, k2);

                if (k < min_k) {
                    color_i_j = sphere.color;
                    min_k = k;
                    drawn_sphere = sphere;
                }
            }

            Point sphere_point = {camera.x + min_k * p.x,
                                  camera.y + min_k * p.y,
                                  camera.z + min_k * p.z};
            Vector normaled_from_center_to_point = Norm(Vector(drawn_sphere.o, sphere_point));

            if (isexist) {
                double dif = 0;

                // проходим по источникам света
                for (auto light: lights) {
                    Vector normaled_from_point_to_light = Norm(Vector(sphere_point, light.p));
                    double cos_angle = max(0.05, DotProd(normaled_from_center_to_point, normaled_from_point_to_light));

                    dif += cos_angle * light.power;
                }
                color_i_j.r *= dif;
                color_i_j.g *= dif;
                color_i_j.b *= dif;
            }


            photo[i][j] = color_i_j;

            p.x += SQW / (W - 1);
        }
    }


    PrintPhoto(photo);
}