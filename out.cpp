#include "out.h"

double const GAMMA_CORECTION = 0.5;

Color Color::v_stepen(double a) const {
    Color thi = *this;
    return {pow(thi.r, a), pow(thi.g, a), pow(thi.b, a)};
}

using namespace std;

void PrintPhoto(vector<vector<Color>> &photo, int max_color) {
    ofstream fout("../ppmfile.ppm");
    fout << "P3\n";
    fout << photo[0].size() << ' ' << photo.size() << '\n';
    fout << max_color << '\n';
    for (auto i: photo) {
        for (auto j: i) {
            fout << int(j.v_stepen(GAMMA_CORECTION).r * max_color) << ' ' <<
                 int(j.v_stepen(GAMMA_CORECTION).g * max_color) << ' ' <<
                 int(j.v_stepen(GAMMA_CORECTION).b * max_color) << '\n';
        }
    }
    fout.close();
}