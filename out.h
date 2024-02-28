#include <vector>
#include <fstream>

using namespace std;

class Color {
public:
    double r;
    double g;
    double b;

    Color() {}

    Color(double r, double g, double b) : r(r), g(g), b(b) {}
};

void PrintPhoto(vector<vector<Color>> &photo, int max_color = 255);