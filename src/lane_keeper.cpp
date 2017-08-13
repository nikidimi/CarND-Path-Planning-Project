#include "lane_keeper.h"
#include <math.h>

Path LaneKeeper::predict(State state, int target_path_length) {
  Path path;

  double prev_s = state.car_s;
  double prev_d = state.car_d;
  double prev_speed = state.car_speed;

  double dist_inc = 0.3;
  double target_speed = 0.4;
  int target_lane = round((prev_d - 2)/4.0);

  double traffic_speed = state.traffic.get_max_speed(prev_s, prev_d, 100 - target_path_length);
  if (traffic_speed > 0) {
    target_speed = traffic_speed;
  }
  double speed = prev_speed;
  double current_s = prev_s;

  for(int i = 1; i < target_path_length; i++)
  {
    double s = fmod(current_s + speed, 6945.554);
    current_s = s;
    double d = target_lane * 4 + 2;

    path.next_s_vals.push_back(s);
    path.next_d_vals.push_back(d);
    path.next_speed_vals.push_back(speed);

    if (speed < target_speed) {
      speed += 0.001;
    }
    else if (speed > target_speed) {
      speed -= 0.001;
    }
  }

  return path;
}
