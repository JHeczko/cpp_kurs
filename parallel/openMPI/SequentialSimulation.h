#ifndef SEQ_SIMULATION_H_

#define SEQ_SIMULATION_H_

#include "Simulation.h"

class  SequentialSimulation: public Simulation {
private:
  int rows, cols, layers;
  void angular_valocity_half_step();
  void new_angle();
  void update_angular_velocity();
  void single_simulation_step();
public:
  SequentialSimulation(Net *const _net, double _I, double _J, double _decay, double _dt);

  void simulation( int steps );
  double total_potential_energy();
  double total_kinetic_energy();

  void calc_energy() {}
  void initialize() {}
  void angles_and_velocities_to_proc_0() {}

};

#endif
