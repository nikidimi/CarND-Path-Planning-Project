#include "lane_keeper.h"

void LaneKeeper::predict(State state, std::vector<double> &next_s_vals, std::vector<double> &next_d_vals, std::vector<double> &next_speed_vals) {
  double prev_s = state.car_s;
  double prev_d = state.car_d;
  double prev_speed = state.car_speed;

  double dist_inc = 0.3;
  double target_speed = 0.4;

  double traffic_speed = state.traffic.get_max_speed(prev_s, prev_d);
  if (traffic_speed > 0) {
    target_speed = traffic_speed;
  }
  double speed = prev_speed;
  double current_s = prev_s;

  for(int i = 1; i < 500; i++)
  {
    double s = current_s + speed;
    current_s = s;
    double d = 6;

    next_s_vals.push_back(s);
    next_d_vals.push_back(d);
    next_speed_vals.push_back(speed);

    if (speed < target_speed) {
      speed += 0.001;
    }
    else if (speed > target_speed) {
      speed -= 0.001;
    }
  }
}
