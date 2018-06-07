#include <vector>
#include <cmath>

/// Класс для точек, находящихся на одной и той же высоте от основания
class Level{
public:
    Level(double height, double precision, double MaxHeight);
    std::vector<std::vector<double>>& getPoints();
private:
    std::vector<std::vector<double>> points;
};