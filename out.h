#include <vector>
#include <fstream>

using namespace std;

class Pixel {
public:
    double r;
    double g;
    double b;

    Pixel() {}

    Pixel(double r, double g, double b): r(r), g(g), b(b) {}
};

void PrintPhoto(vector<vector<Pixel>>& photo, int max_color = 255);