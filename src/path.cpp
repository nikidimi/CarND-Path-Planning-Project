#include "path.h"
#include <cmath>

bool Path::operator< (const Path& right) const {
  return cost() < right.cost();
}

double Path::cost() const {
  if (next_d_vals.size() == 0) return 0;

  double prev = next_d_vals[0];
  double d_change = 0;

  for(int i = 1; i < next_d_vals.size(); i++) {
    d_change += std::abs(next_d_vals[i] - prev);
    prev = next_d_vals[i];
  }
  return d_change;
}
