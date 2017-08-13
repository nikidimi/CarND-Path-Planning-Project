#include "behaviour.h"
#include "lane_keeper.h"
#include "lane_changer.h"
#include <algorithm>

void Behaviour::predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals) {
  std::vector<double> next_s_vals, next_d_vals, next_speed_vals;
  int target_path_length = 100 - state.previous_path_x.size();

  if (state.previous_path_x.size() > 2) {
    std::vector<double> old_s_d_v = get_old_s_d(state, next_x_vals, next_y_vals);
    state.car_s = old_s_d_v[0];
    state.car_d = old_s_d_v[1];
    state.car_speed = old_s_d_v[2];
  }

  std::vector<Path> paths;
  if (state.car_d > 4) {
    LaneChanger lane_changer;
    lane_changer.lane_change = -1;
    paths.push_back(lane_changer.predict(state, target_path_length));
  }
  if (state.car_d < 8) {
    LaneChanger lane_changer;
    lane_changer.lane_change = 1;
    paths.push_back(lane_changer.predict(state, target_path_length));
  }
  LaneKeeper lane_keeper;
  paths.push_back(lane_keeper.predict(state, target_path_length));

  std::sort(paths.begin(), paths.end());

  for(int i = 0; i < paths[0].next_s_vals.size(); i++)
  {
    double s = paths[0].next_s_vals[i];
    double d = paths[0].next_d_vals[i];
    std::vector<double> cartesian = getXY(s, d);

    old_x.push_back(cartesian[0]);
    old_y.push_back(cartesian[1]);
    old_s.push_back(s);
    old_d.push_back(d);
    old_speed.push_back(paths[0].next_speed_vals[i]);
    next_x_vals.push_back(cartesian[0]);
    next_y_vals.push_back(cartesian[1]);
  }
}

std::vector<double> Behaviour::getXY(double s, double d)
{
  double EPSILON = 2.0;
	double seg_x = _s_x(s);
	double seg_y = _s_y(s);

  double heading = atan2((_s_y(s + EPSILON)-_s_y(s - EPSILON)),(_s_x(s + EPSILON)-_s_x(s - EPSILON)));
	double perp_heading = heading-M_PI/2;

	double x = seg_x + d*cos(perp_heading);
	double y = seg_y + d*sin(perp_heading);

	return {x,y};
}

std::vector<double> Behaviour::get_old_s_d(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals) {
  for(int i = 0; i < old_x.size(); i++) {
    if (abs(state.car_x - old_x[i]) < 0.001 && abs(state.car_y - old_y[i]) < 0.001) {
      old_speed.erase(old_speed.begin(), old_speed.begin() + i);
      old_x.erase(old_x.begin(), old_x.begin() + i);
      old_y.erase(old_y.begin(), old_y.begin() + i);
      old_s.erase(old_s.begin(), old_s.begin() + i);
      old_d.erase(old_d.begin(), old_d.begin() + i);

      break;
    }
  }

  double prev_s, prev_d, prev_speed;

  prev_s = old_s.back();
  prev_d = old_d.back();
  prev_speed = old_speed.back();

  for(int i = 0; i < state.previous_path_x.size(); i++) {
    next_x_vals.push_back(state.previous_path_x[i]);
    next_y_vals.push_back(state.previous_path_y[i]);
  }

  return {prev_s, prev_d, prev_speed};
}
