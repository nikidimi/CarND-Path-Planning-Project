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

double Traffic::get_max_speed(double s, double d) {
  for(Car &car: _cars) {
    if (car.d < d - 2 || car.d > d + 2) {
      continue;
    }
    if (car.s > s && abs(car.s - s) < 1) {
      std::cout << "following car s=" << car.s << " d=" << car.d;
      std::cout << " delta s=" << s << " delta d=" << s << std::endl;
      return car.get_speed();
    }
  }

  return 0;
}
