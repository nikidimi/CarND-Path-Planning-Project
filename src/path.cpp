#include "path.h"
#include <cmath>
#include <iostream>

bool Path::operator< (const Path& right) const {
  return cost < right.cost;
}

void Path::calc_cost(Traffic traffic, int t) {
  cost = d_cost() + 100 * obstructed_cost(traffic, t) + 100000 * collision_cost(traffic, t);
}


double Path::d_cost() const {
  if (next_d_vals.size() == 0) return 0;

  double prev = next_d_vals[0];
  double d_change = 0;

  for(int i = 1; i < next_d_vals.size(); i++) {
    d_change += std::abs(next_d_vals[i] - prev);
    prev = next_d_vals[i];
  }
  return d_change/4.0;
}

double Path::obstructed_cost(Traffic traffic, int t) const {
  if (next_speed_vals.size() == 0) return 0;
  double s = traffic.get_max_speed(next_s_vals.back(), next_d_vals.back(), t + next_speed_vals.size());
  return s > 0;
}

double Path::collision_cost(Traffic traffic, int t) const {
  if (next_speed_vals.size() == 0) return 0;
  for(int i = 0; i < next_d_vals.size(); i++) {
    if (traffic.check_for_collision(next_s_vals[i], next_d_vals[i], t + i)) {
      return 1.0;
    }
  }
  return 0;
}
