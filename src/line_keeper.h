#include "quintic_solver.h"
#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"

class LineKeeper {
public:
  LineKeeper(tk::spline s_x, tk::spline s_y): _s_x(s_x), _s_y(s_y) {};
  std::vector<double> getXY(double s, double d);
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals);
private:
  void get_old_s_d(State state);
  tk::spline _s_x;
  tk::spline _s_y;
  double prev_s = 0;
  double prev_speed = 0;
  double prev_d = 0;
  std::vector<double> old_x;
  std::vector<double> old_y;
  std::vector<double> old_s;
  std::vector<double> old_d;
  std::vector<double> old_speed;

  int step = 0;
  double last_car_id = -1;
  bool quit = false;
};
