#include "lane_keeper.h"
#include "spline.h"

class Behaviour {
public:
  Behaviour(tk::spline s_x, tk::spline s_y): _s_x(s_x), _s_y(s_y) {};
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals);
private:
  LaneKeeper lane_keeper;

  std::vector<double> old_x;
  std::vector<double> old_y;
  std::vector<double> old_s;
  std::vector<double> old_d;
  std::vector<double> old_speed;

  std::vector<double> getXY(double s, double d);
  std::vector<double> get_old_s_d(State state);
  tk::spline _s_x;
  tk::spline _s_y;
};
