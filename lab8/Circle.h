#include <vector>
#include <cmath>

// Класс, хранящий точки, лежащие на одном из эллипсов, образующих основание.
class Circle {
public:
    Circle(double precision_radius, double precision_segments);
    std::vector<std::vector<double>>& getPoints();
private:
    std::vector<std::vector<double>> points;
};

