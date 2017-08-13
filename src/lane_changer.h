#ifndef LANE_CHANGE_HPP
#define LANE_CHANGE_HPP

#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"

class LaneChanger {
public:
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals,
    std::vector<double> &next_speed_vals, int target_path_length);
  int lane_change = 0;
};

#endif
