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
    if (abs(car.s - s) < 50 && car.s > s) {
      std::cout << "following car " << car.id << " s=" << car.s << " d=" << car.d;
      std::cout << " delta_x " << car.delta_x << " delta_y=" << car.delta_y << " vel=" << car.get_speed();
      std::cout << " delta s=" << s << " delta d=" << d << std::endl;
      return 0.9 * car.get_speed();
    }
  }

  return 0;
}
