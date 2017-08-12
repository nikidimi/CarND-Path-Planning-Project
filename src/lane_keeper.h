#include "quintic_solver.h"
#include <vector>
#include "spline.h"
#include "traffic.h"
#include "state.h"

class LaneKeeper {
public:
  LaneKeeper(tk::spline s_x, tk::spline s_y): _s_x(s_x), _s_y(s_y) {};
  std::vector<double> getXY(double s, double d);
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals);
private:
  std::vector<double> get_old_s_d(State state);
  tk::spline _s_x;
  tk::spline _s_y;

  std::vector<double> old_x;
  std::vector<double> old_y;
  std::vector<double> old_s;
  std::vector<double> old_d;
  std::vector<double> old_speed;
};
