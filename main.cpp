#include <map>
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

void Drawing(Color &color_i_j, vector<Sphere> &spheres, vector<Light> &lights, Point &camera, Point &p) {
    double min_k = 1e9;
    Sphere drawn_sphere;

    // проходим по всем сферам
    for (auto sphere: spheres) {
        double k = sphere.intersection(camera, p);

        if (k < min_k) {
            color_i_j = sphere.color;
            min_k = k;
            drawn_sphere = sphere;
        }
    }

    Point sphere_point = {camera.x + min_k * p.x,
                          camera.y + min_k * p.y,
                          camera.z + min_k * p.z};
    Vector normaled_from_center_to_point = Vector(drawn_sphere.o, sphere_point).Norm();

    if (min_k < 1e9) {
        double dif = 0;
        double spec = 0;

        // проходим по источникам света
        for (auto light: lights) {

            bool f = false;
            // проходим по всем сферам для обнаружения других сфер
            for (auto sphere: spheres) {
                double k = sphere.intersection(light.p, sphere_point);

                if (k < 0.99999999999) {
                    f = true;
                    break;
                }
            }
            if (f) continue;

            Vector normaled_from_point_to_light = Vector(sphere_point, light.p).Norm();

            double diffuse = max(0.0, Vector::DotProd(normaled_from_center_to_point, normaled_from_point_to_light));
            double specular = max(0.0, pow(Vector::DotProd(Vector(sphere_point, camera).Norm(),
                                                           normaled_from_point_to_light.Mult(-1).Reflect(
                                                                   normaled_from_center_to_point)),
                                           drawn_sphere.mat.specular));
            dif += diffuse * light.power;
            spec += specular * light.power;
        }
        color_i_j.r *= dif * drawn_sphere.mat.difAlbedo;
        color_i_j.r += spec * drawn_sphere.mat.specAlbedo;
        color_i_j.r *= drawn_sphere.mat.refl;

        color_i_j.g *= dif * drawn_sphere.mat.difAlbedo;
        color_i_j.g += spec * drawn_sphere.mat.specAlbedo;
        color_i_j.g *= drawn_sphere.mat.refl;

        color_i_j.b *= dif * drawn_sphere.mat.difAlbedo;
        color_i_j.b += spec * drawn_sphere.mat.specAlbedo;
        color_i_j.b *= drawn_sphere.mat.refl;
    }
}

void Render(Point &camera, vector<vector<Color>> &photo, vector<Sphere> &spheres, vector<Light> &lights) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            Point p = {-SQW / 2 + (double(j) * SQW) / (W - 1), SQH / 2 - (double(i) * SQH) / (H - 1), SQD};
            Color color_i_j = photo[i][j];

            Drawing(color_i_j, spheres, lights, camera, p);

            photo[i][j] = color_i_j;
        }
    }

    PrintPhoto(photo);
}

int main() {
    vector<vector<Color>> photo(H, vector<Color>(W, BG)); // картинка

    Point camera = Point(0, 0, 0); // позиция игрока

    map<string, Material> Materials{
            {"basa", Material(0.5, 0.3, 511, 0.8)}
    };

    // сферы:
    int sphereCol = 2;
    vector<Sphere> spheres = {
            Sphere({1, 1.5, 5}, 1, {0.8, 0.7, 0.3}, Materials["basa"]),
            Sphere({-1, -2, 6}, 1.2, {1, 0, 1}, Materials["basa"])
    };

    // источники света:
    int lightCol = 1;
    vector<Light> lights = {
            Light({4, 4, 2}, 1),
            Light({10, 0, 5}, 1)
    };

    Render(camera, photo, spheres, lights);
}