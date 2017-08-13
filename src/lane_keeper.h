#ifndef LANE_KEEPER_HPP
#define LANE_KEEPER_HPP

#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"
#include "path.h"

class LaneKeeper {
public:
  Path predict(State state, int target_path_length);
};

#endif
