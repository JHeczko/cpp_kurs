#include "Net.h"
#include <math.h>

#ifndef PHYSICS_H_

#define PHYSICS_H_

class Physics {
private:
  const double decay;
  Net *const net;
  int cols;
  int rows;
  int layers;

public:
  Physics(Net *const _net, double _decay) : decay(_decay), net(_net) {}

  double torque(int col, int row, int layer);
  double local_potential_energy(int col, int row, int layer);
  double local_kinetic_energy(int col, int row, int layer);

  double total_potential_energy();
  double total_kinetic_energy();
};

#endif