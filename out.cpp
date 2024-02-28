#include "out.h"

using namespace std;

void PrintPhoto(vector<vector<Color>> &photo, int max_color) {
    ofstream fout("../ppmfile.ppm");
    fout << "P3\n";
    fout << photo[0].size() << ' ' << photo.size() << '\n';
    fout << max_color << '\n';
    for (auto i: photo) {
        for (auto j: i) {
            fout << int(j.r * max_color) << ' ' <<
                 int(j.g * max_color) << ' ' <<
                 int(j.b * max_color) << '\n';
        }
    }
    fout.close();
}