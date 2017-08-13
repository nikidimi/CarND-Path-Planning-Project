#include "traffic.h"
#include <algorithm>
#include <iostream>

Traffic::Traffic(std::vector<std::vector<double> > data) {
  for(auto car_data: data) {
    Car car(car_data);
    _cars.push_back(car);
  }
  std::sort(_cars.begin(), _cars.end());
}

double Traffic::get_max_speed(double s, double d, double t) {
  for(Car &car: _cars) {
    double future_s = car.s + car.get_speed() * t;
    if (car.d < d - 2 || car.d > d + 2) {
      continue;
    }
    if (abs(future_s - s) < 50 && future_s > s) {
      return 0.9 * car.get_speed();
    }
  }

  return 0;
}

bool Traffic::check_for_collision(double s, double d, double t) {
  for(Car &car: _cars) {
    double future_s = car.s + car.get_speed() * t;
    if (car.d < d - 2 || car.d > d + 2) {
      continue;
    }
    if (abs(future_s - s) < 10) {
      return true;
    }
  }

  return false;
}
