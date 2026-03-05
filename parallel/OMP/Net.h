#ifndef NET_H_
#define NET_H_

#include "Grid3D.h"
#include <math.h>

class Net {
private:
  Grid3D *angle;
  Grid3D *angular_velocity;

  double wrap_angle(double x) {
    const double TWO_PI = 6.283185307179586;
    x = fmod(x, TWO_PI);
    if (x < 0)
      x += TWO_PI;
    return x;
  }

public:
  Net(int cols, int rows, int layers);

  double get_angle(int col, int row, int layer) {
    return angle->get(col, row, layer);
  }

  double get_angular_velocity(int col, int row, int layer) {
    return angular_velocity->get(col, row, layer);
  }

  void set_angle(int col, int row, int layer, double value) {
    angle->set(col, row, layer, wrap_angle(value));
  }

  void set_angular_velocity(int col, int row, int layer, double value) {
    angular_velocity->set(col, row, layer, value);
  }

  int get_layers() { return angle->get_layers(); }

  int get_cols() { return angle->get_cols(); }

  int get_rows() { return angle->get_rows(); }
};

#endif