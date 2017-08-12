#include "behaviour.h"

void Behaviour::predict(State state, std::vector<double> &next_x_vals, std::vector<double> &next_y_vals) {
  lane_keeper.predict(state, next_x_vals, next_y_vals);
}
