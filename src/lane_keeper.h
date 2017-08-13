#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"

class LaneKeeper {
public:
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals,
    std::vector<double> &next_speed_vals, int target_path_length);
};
