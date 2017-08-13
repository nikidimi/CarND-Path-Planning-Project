#include "behaviour.h"

void Behaviour::predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals) {
  std::vector<double> next_s_vals, next_d_vals, next_speed_vals;

  if (state.previous_path_x.size() > 2) {
    std::vector<double> old_s_d_v = get_old_s_d(state);
    state.car_s = old_s_d_v[0];
    state.car_d = old_s_d_v[1];
    state.car_speed = old_s_d_v[2];
  }

  lane_keeper.predict(state, next_s_vals, next_d_vals, next_speed_vals);

  for(int i = 0; i < next_s_vals.size(); i++)
  {
    double s = next_s_vals[i];
    double d = next_d_vals[i];
    std::vector<double> cartesian = getXY(s, d);

    old_x.push_back(cartesian[0]);
    old_y.push_back(cartesian[1]);
    old_s.push_back(s);
    old_d.push_back(d);
    old_speed.push_back(next_speed_vals[i]);
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

std::vector<double> Behaviour::get_old_s_d(State state) {
  double prev_s, prev_d, prev_speed;

  for(int i = 0; i < old_x.size(); i++) {
    if (abs(state.car_x - old_x[i]) < 0.001 && abs(state.car_y - old_y[i]) < 0.001) {
      prev_s = old_s[i];
      prev_d = old_d[i];
      prev_speed = old_speed[i];
      old_speed.clear();
      old_x.clear();
      old_y.clear();
      old_s.clear();
      old_d.clear();

      return {prev_s, prev_d, prev_speed};
    }
  }
}
