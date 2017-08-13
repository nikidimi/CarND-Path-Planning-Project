#include "lane_changer.h"
#include <math.h>
#include "spline.h"

Path LaneChanger::predict(State state, int target_path_length) {
  Path path;

  double prev_s = state.car_s;
  double prev_d = state.car_d;
  double prev_speed = state.car_speed;

  double dist_inc = 0.3;
  double target_speed = 0.4;

  double speed = prev_speed;
  double current_s = prev_s;

  tk::spline spline_d;

  int current_lane = round((prev_d - 2)/4.0);
  int target_lane = current_lane + lane_change;

  spline_d.set_points({0, 10, 80, 100}, {current_lane * 4 + 2, current_lane * 4 + 2, target_lane * 4 + 2, target_lane * 4 + 2});

  for(int i = 1; i < 100; i++)
  {
    double s = fmod(current_s + speed, 6945.554);
    current_s = s;
    double d = spline_d(i);

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
