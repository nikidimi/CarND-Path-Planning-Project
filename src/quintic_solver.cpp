#include "quintic_solver.h"

void QuinticSolver::fit(double s, double speed, double acceleration, double target_s, double target_speed, double target_acceleration, int T) {
  Eigen::MatrixXd A = Eigen::MatrixXd(3, 3);
  A << T*T*T, T*T*T*T, T*T*T*T*T,
       3*T*T, 4*T*T*T,5*T*T*T*T,
       6*T, 12*T*T, 20*T*T*T;

  Eigen::MatrixXd B = Eigen::MatrixXd(3,1);
  B << target_s-(s+speed*T+.5*acceleration*T*T),
       target_speed-(speed+acceleration*T),
       target_acceleration-acceleration;

  Eigen::MatrixXd Ai = A.inverse();

  Eigen::MatrixXd C = Ai*B;

  std::vector <double> result = {s, speed, .5*acceleration};
  for(int i = 0; i < C.size(); i++)
  {
    result.push_back(C.data()[i]);
  }

  coeff = result;
}

double QuinticSolver::operator()(double t) {
  return coeff[0] + coeff[1] * t + coeff[2] * t * t + coeff[3] * t * t * t + coeff[4] * t * t * t * t + coeff[5] * t * t * t * t * t;
}
