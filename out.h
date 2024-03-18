#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Color {
public:
    double r;
    double g;
    double b;

    Color() {}

    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color v_stepen(double a) const;
};

void PrintPhoto(vector<vector<Color>> &photo, int max_color = 255);