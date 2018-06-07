#include <vector>
#include <cmath>

using namespace std::vector;

class Circle {
public:
    Circle(double precision_radius, double precision_segments);
    vector<vector<double>>& getPoints();
private:
    vector<vector<double>> points;
};

