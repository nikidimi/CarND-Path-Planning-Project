#include <vector>

class Car {
public:
  Car(std::vector<double> data);
  double get_speed();
  bool operator <(const Car& rhs);

  double id;
  double x;
  double y;
  double delta_x;
  double delta_y;
  double s;
  double d;
};
