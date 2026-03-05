#include "Simulation.h"
#include "SequentialSimulation.h"

SequentialSimulation::SequentialSimulation(Net *const _net, double _I, double _J, double _decay, double _dt):Simulation( _net, _I, _J, _decay, _dt ) {
    cols = net->get_cols();
    rows = net->get_rows();
    layers = net->get_layers();
  }

double SequentialSimulation::total_potential_energy() {
  double result = 0;
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        result += physics->local_potential_energy(col, row, layer);
      }
  return -J * 0.5 * result;
}

double SequentialSimulation::total_kinetic_energy() {
  double result = 0;
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++)
        result += physics->local_kinetic_energy(col, row, layer);
  return 0.5 * I * result;
}

void SequentialSimulation::simulation( int steps ) {
  for ( int i = 0; i < steps; i++ )
    single_simulation_step();
}

void SequentialSimulation::single_simulation_step() {
  angular_valocity_half_step();
  new_angle();
  update_angular_velocity();
}

void SequentialSimulation::angular_valocity_half_step() {
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angular_velocity(
            col, row, layer,
            net->get_angular_velocity(col, row, layer) + reduced_time * physics->torque(col, row, layer));
      }
}

void SequentialSimulation::new_angle() {
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angle(
            col, row, layer,
            net->get_angle(col, row, layer) + dt * net->get_angular_velocity(col, row, layer));
      }
}

void SequentialSimulation::update_angular_velocity() {
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angular_velocity(
            col, row, layer,
            net->get_angular_velocity(col, row, layer) + reduced_time * physics->torque(col, row, layer));
      }
}
