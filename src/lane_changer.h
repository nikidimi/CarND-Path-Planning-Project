#ifndef LANE_CHANGE_HPP
#define LANE_CHANGE_HPP

#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"
#include "path.h"

class LaneChanger {
public:
  Path predict(State state, int target_path_length);
  int lane_change = 0;
};

#endif
