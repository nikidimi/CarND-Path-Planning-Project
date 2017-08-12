#include "car.h"
#include "math.h"

Car::Car(std::vector<double> data) {
  id = data[0];
  x = data[1];
  y = data[2];
  delta_x = data[3];
  delta_y = data[4];
  s = data[5];
  d = data[6];
}

double Car::get_speed() {
  return sqrt(delta_x * delta_x + delta_y * delta_y)/50.0;
}

bool Car::operator<(const Car& rhs) {
  return s > rhs.s;
}
