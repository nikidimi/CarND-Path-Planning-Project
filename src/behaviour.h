#include "lane_keeper.h"
#include "spline.h"

class Behaviour {
public:
  Behaviour(tk::spline s_x, tk::spline s_y): lane_keeper(s_x, s_y) {};
  void predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals);
private:
  LaneKeeper lane_keeper;
};
