#include "state.h"

State::State(nlohmann::json json): sensor_fusion(json["sensor_fusion"].get<std::vector<std::vector<double > > >()), traffic(sensor_fusion) {
  car_x = json["x"];
  car_y = json["y"];
  car_s = json["s"];
  car_d = json["d"];
  car_yaw = json["yaw"];
  car_speed = json["speed"];

  // Previous path data given to the Planner
  previous_path_x = json["previous_path_x"].get<std::vector<double> >();
  previous_path_y = json["previous_path_y"].get<std::vector<double> >();
  // Previous path's end s and d values
  end_path_s = json["end_path_s"];
  end_path_d = json["end_path_d"];

}
