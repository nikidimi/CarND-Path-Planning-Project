#ifndef TRAFFIC_HPP
#define TRAFFIC_HPP

#include <vector>
#include "car.h"

class Traffic {
public:
  Traffic(std::vector<std::vector<double> > data);
  double get_max_speed(double s, double d);
private:
  std::vector<Car> _cars;
};

#endif
