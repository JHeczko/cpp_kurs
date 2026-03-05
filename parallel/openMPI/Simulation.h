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
  virtual void calc_energy() = 0;
  virtual double total_potential_energy() = 0;
  virtual double total_kinetic_energy() = 0;
  virtual void simulation( int steps ) = 0;
  virtual void initialize() = 0;
  virtual void angles_and_velocities_to_proc_0() = 0;
};

#endif
