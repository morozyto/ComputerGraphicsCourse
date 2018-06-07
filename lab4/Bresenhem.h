#include "Pixel.h"
#include <vector>

using namespace std;

static int sign(int y) {
    if (y > 0) return 1;
    if (y < 0) return -1;
    else return 0;
}

vector<Pixel> Bresenham(vector<int>& point1, vector<int>& point2) {

    int x1 = point1[0], y1 = point1[1];
    int x2 = point2[0], y2 = point2[1];
    vector<Pixel> Points;
    if (x1 == x2 && y1 == y2) {
        Points.emplace_back(x1, y1);
        return Points;
    }
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);

    bool change;

    if (dy > dx) {
        int t = dx;
        dx = dy;
        dy = t;
        change = true;
    } else change = false;

    int e = 2*dy - dx;

    for (int i = 1; i <= dx; i++) {
        Points.emplace_back(x, y);
        while (e >= 0) {
            if (change) x += s1;
            else y += s2;

            Points.emplace_back(x, y);
            e -= 2*dx;
        }
        if (change) y += s2;
        else x += s1;

        e += 2*dy;
    }
    return Points;
}
