#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "Eigen-3.3/Eigen/Dense"

class QuinticSolver {
public:
  void fit(double s, double speed, double acceleration, double target_s, double target_speed, double target_acceleration, int T);
  double operator()(double t);

private:
  std::vector<double> coeff;
};
