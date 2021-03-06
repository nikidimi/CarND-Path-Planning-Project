#ifndef TRAFFIC_HPP
#define TRAFFIC_HPP

#include <vector>
#include "car.h"

class Traffic {
public:
  Traffic(std::vector<std::vector<double> > data);
  double get_max_speed(double s, double d, double t = 0);
  bool check_for_collision(double s, double d, double t = 0);
private:
  std::vector<Car> _cars;

};

#endif
