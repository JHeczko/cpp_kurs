#ifndef SIMULATION_H_

#define SIMULATION_H_

#include "Physics.h"

class Simulation {
protected:
  Net *const net;
  Physics *const physics;
  const double dt;
  const double reduced_time;
  const double I;
  const double J;

public:
  Simulation(Net *const _net, double _I, double _J, double _decay, double _dt);
  virtual double total_potential_energy() = 0;
  virtual double total_kinetic_energy() = 0;
  virtual void simulation(int steps) = 0;
  virtual void correlation(double *histogram, int bins, double angle) = 0;
  virtual double self_correlation() = 0;
};

#endif