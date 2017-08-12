#include "line_keeper.h"
#include <math.h>

std::vector<double> LineKeeper::getXY(double s, double d)
{

//	double heading = atan2((maps_y[wp2]-maps_y[prev_wp]),(maps_x[wp2]-maps_x[prev_wp]));
	// the x,y,s along the segment
	//double seg_s = (s-maps_s[prev_wp]);

  double EPSILON = 2.0;
	double seg_x = _s_x(s);
	double seg_y = _s_y(s);

  double heading = atan2((_s_y(s + EPSILON)-_s_y(s - EPSILON)),(_s_x(s + EPSILON)-_s_x(s - EPSILON)));
	double perp_heading = heading-M_PI/2;

	double x = seg_x + d*cos(perp_heading);
	double y = seg_y + d*sin(perp_heading);

	return {x,y};
}

/*void estimate_initial_position() {
  double diff = 10000;
  double min_s = car_s, min_d = car_d;

  std::vector<double> cartesian = getXY(car_s, car_d);
  //cout << "start diff=" << abs(cartesian[0] - car_x) + abs(cartesian[1] - car_y) << endl;

  if (end_path_s == 0) {
    for (double s = car_s - 1.0; s < car_s + 1.0; s+=0.01) {
      for (double d = car_d - 1.0; d < car_d + 1.0; d+=0.01) {
        std::vector<double> cartesian = getXY(s, d);

        if (abs(cartesian[0] - car_x) + abs(cartesian[1] - car_y) < diff) {
          diff = abs(cartesian[0] - car_x) + abs(cartesian[1] - car_y);
          min_s = s;
          min_d = d;
        }
      }
    }
    prev_d = min_d;
    prev_s = min_s;
  }
}*/

void LineKeeper::get_old_s_d(State state) {
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
      std::cout << "prev_speed=" << prev_speed << std::endl;
      return;
    }
  }
}

void LineKeeper::predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals) {
  if (quit) {
    for(int i = 0; i < state.previous_path_x.size(); i++)
    {
      next_x_vals.push_back(state.previous_path_x[i]);
      next_y_vals.push_back(state.previous_path_y[i]);

    }
    return;
  }

  if (prev_speed == 0) {
    prev_s = state.car_s;
    prev_d = state.car_d;
  }
  else {
    get_old_s_d(state);
  }

  double dist_inc = 0.3;
  //cout << "diff=" << diff << " delta_s=" << car_s - min_s << endl;


  double target_speed = 0.4;
  /*if (step % 100 > 50) {
    target_speed = 0.1;
    std::cout << "SLOW" << std::endl;
  }*/
  double t = 500;
  double acc = (target_speed-prev_speed)/t;
  double target_s = prev_s + t * prev_speed + 1.2*acc * t * t/2;

  double traffic_speed = 0;
  state.traffic.last_id = last_car_id;
  //double traffic_speed = state.traffic.get_max_speed(target_s, prev_d);
  //if (traffic_speed > 0) {
  //  target_speed = traffic_speed;
  //  target_s -= (prev_speed - traffic_speed) * t / 2;
  //}

  QuinticSolver solver, solver_d;

  solver.fit(prev_s, prev_speed, 0, target_s, target_speed, 0, t);
  solver_d.fit(prev_d, 0, 0, 6, 0, 0, t);

  double current_s = prev_s;
  for(int i = 1; i < 500; i++)
  {
    double s = solver(i);
    double d = solver_d(i);
    std::vector<double> cartesian = getXY(s, d);

    old_x.push_back(cartesian[0]);
    old_y.push_back(cartesian[1]);
    old_s.push_back(s);
    old_d.push_back(d);
    old_speed.push_back(s - current_s);
    next_x_vals.push_back(cartesian[0]);
    next_y_vals.push_back(cartesian[1]);
    current_s = s;
  }

  quit = true;


  prev_s = current_s;
  prev_d = 6;
  prev_speed = target_speed;
  step++;
  last_car_id = state.traffic.last_id;
}
