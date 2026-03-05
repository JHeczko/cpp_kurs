#ifndef SEQ_SIMULATION_H_

#define SEQ_SIMULATION_H_

#include "Simulation.h"

class SequentialSimulation : public Simulation {
private:
  int rows, cols, layers;
  void angular_valocity_half_step();
  void new_angle();
  void single_simulation_step();

public:
  SequentialSimulation(Net *const _net, double _I, double _J, double _decay,
                       double _dt);

  void simulation(int steps);
  double total_potential_energy();
  double total_kinetic_energy();
  void correlation(double *histogram, int bins, double angle);
  double self_correlation();
};

#endif
