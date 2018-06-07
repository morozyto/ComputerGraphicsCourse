#include <vector>
#include <cmath>

using namespace std::vector;
/// Класс для точек, находящихся на одной и той же высоте от основания
class Level{
public:
    Level(double height, double precision, double MaxHeight);
    vector<vector<double>>& getPoints();
private:
    vector<vector<double>> points;
};