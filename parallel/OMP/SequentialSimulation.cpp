#include "SequentialSimulation.h"
#include "Simulation.h"
#include <math.h>

SequentialSimulation::SequentialSimulation(Net *const _net, double _I,
                                           double _J, double _decay, double _dt)
    : Simulation(_net, _I, _J, _decay, _dt) {
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

void SequentialSimulation::simulation(int steps) {
  for (int i = 0; i < steps; i++)
    single_simulation_step();
}

void SequentialSimulation::single_simulation_step() {
  angular_valocity_half_step();
  new_angle();
  angular_valocity_half_step();
}

void SequentialSimulation::angular_valocity_half_step() {
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angular_velocity(col, row, layer,
                                  net->get_angular_velocity(col, row, layer) +
                                      reduced_time *
                                          physics->torque(col, row, layer));
      }
}

void SequentialSimulation::new_angle() {
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angle(col, row, layer,
                       net->get_angle(col, row, layer) +
                           dt * net->get_angular_velocity(col, row, layer));
      }
}

void SequentialSimulation::correlation(double *histogram, int bins,
                                       double angle) {
  double toBin = bins / 2.0;
  int idx;

  for (int bin = 0; bin < bins; bin++)
    histogram[bin] = 0.0;

  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        idx = (int)((cos(angle - net->get_angle(col, row, layer)) + 1.0) *
                    toBin) %
              bins;
        histogram[idx] += 1.0;
      }

  double vol = cols * rows * layers;
  for (int bin = 0; bin < bins; bin++)
    histogram[bin] /= vol;
}

double SequentialSimulation::self_correlation() {
  double sum = 0.0;
  double angle;

  for (int layer = 1; layer < layers - 1; layer++)
    for (int row = 1; row < rows - 1; row++)
      for (int col = 1; col < cols - 1; col++) {
        angle = net->get_angle(col, row, layer);
        sum += cos(angle - net->get_angle(col + 1, row, layer));
        sum += cos(angle - net->get_angle(col - 1, row, layer));
        sum += cos(angle - net->get_angle(col, row + 1, layer));
        sum += cos(angle - net->get_angle(col, row - 1, layer));
        sum += cos(angle - net->get_angle(col, row, layer + 1));
        sum += cos(angle - net->get_angle(col, row, layer - 1));
      }

  double vol = 6 * (cols - 2) * (rows - 2) * (layers - 2);

  return sum / vol;
}
