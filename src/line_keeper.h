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
  tk::spline _s_x;
  tk::spline _s_y;
  double prev_s = 0;
  double prev_speed = 0;
  double prev_d = 0;
};
