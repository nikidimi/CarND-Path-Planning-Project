#ifndef PATH_HPP
#define PATH_HPP

#include <vector>

class Path {
public:
  std::vector<double> next_s_vals;
  std::vector<double> next_d_vals;
  std::vector<double> next_speed_vals;

  bool operator< (const Path& right) const;
  double cost() const;
};


#endif
