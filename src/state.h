#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include "json.hpp"
#include "traffic.h"

class State {
public:
  State(nlohmann::json json);
  double car_x;
  double car_y;
  double car_s;
  double car_d;
  double car_yaw;
  double car_speed;

  // Previous path data given to the Planner
  std::vector<double>  previous_path_x;
  std::vector<double>  previous_path_y;
  // Previous path's end s and d values
  double end_path_s;
  double end_path_d;

  // Sensor Fusion Data, a list of all other cars on the same side of the road.
  std::vector<std::vector<double > > sensor_fusion;
  Traffic traffic;
};

#endif
