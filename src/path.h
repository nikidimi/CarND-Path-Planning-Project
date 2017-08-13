#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "traffic.h"

class Path {
public:
  std::vector<double> next_s_vals;
  std::vector<double> next_d_vals;
  std::vector<double> next_speed_vals;

  bool operator< (const Path& right) const;
  void calc_cost(Traffic traffic, int t);

  double d_cost() const;
  double obstructed_cost(Traffic traffic, int t) const;
  double collision_cost(Traffic traffic, int t) const;

private:
  double cost;
};


#endif
