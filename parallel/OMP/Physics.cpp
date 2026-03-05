#include "Physics.h"
#include <math.h>

double Physics::torque(int col, int row, int layer) {
  double theta = net->get_angle(col, row, layer);
  double sumNN = sin(theta - net->get_angle(col, row, layer + 1));
  sumNN += sin(theta - net->get_angle(col, row, layer - 1));
  sumNN += sin(theta - net->get_angle(col, row + 1, layer));
  sumNN += sin(theta - net->get_angle(col, row - 1, layer));
  sumNN += sin(theta - net->get_angle(col - 1, row, layer));
  sumNN += sin(theta - net->get_angle(col + 1, row, layer));
  double sumNNN = 0.0;
  sumNNN += sin(theta - net->get_angle(col + 1, row, layer + 1));
  sumNNN += sin(theta - net->get_angle(col - 1, row, layer + 1));
  sumNNN += sin(theta - net->get_angle(col, row + 1, layer + 1));
  sumNNN += sin(theta - net->get_angle(col, row - 1, layer + 1));
  sumNNN += sin(theta - net->get_angle(col + 1, row, layer - 1));
  sumNNN += sin(theta - net->get_angle(col - 1, row, layer - 1));
  sumNNN += sin(theta - net->get_angle(col, row + 1, layer - 1));
  sumNNN += sin(theta - net->get_angle(col, row - 1, layer - 1));
  sumNNN += sin(theta - net->get_angle(col + 1, row + 1, layer));
  sumNNN += sin(theta - net->get_angle(col - 1, row + 1, layer));
  sumNNN += sin(theta - net->get_angle(col + 1, row - 1, layer));
  sumNNN += sin(theta - net->get_angle(col - 1, row - 1, layer));
  return (sumNN + sumNNN * decay);
}

double Physics::local_potential_energy(int col, int row, int layer) {
  double theta = net->get_angle(col, row, layer);
  double sumNN = cos(theta - net->get_angle(col, row, layer + 1));
  sumNN += cos(theta - net->get_angle(col, row, layer - 1));
  sumNN += cos(theta - net->get_angle(col, row + 1, layer));
  sumNN += cos(theta - net->get_angle(col, row - 1, layer));
  sumNN += cos(theta - net->get_angle(col - 1, row, layer));
  sumNN += cos(theta - net->get_angle(col + 1, row, layer));
  double sumNNN = cos(theta - net->get_angle(col + 1, row, layer + 1));
  sumNNN += cos(theta - net->get_angle(col - 1, row, layer + 1));
  sumNNN += cos(theta - net->get_angle(col, row + 1, layer + 1));
  sumNNN += cos(theta - net->get_angle(col, row - 1, layer + 1));
  sumNNN += cos(theta - net->get_angle(col + 1, row, layer - 1));
  sumNNN += cos(theta - net->get_angle(col - 1, row, layer - 1));
  sumNNN += cos(theta - net->get_angle(col, row + 1, layer - 1));
  sumNNN += cos(theta - net->get_angle(col, row - 1, layer - 1));
  sumNNN += cos(theta - net->get_angle(col + 1, row + 1, layer));
  sumNNN += cos(theta - net->get_angle(col - 1, row + 1, layer));
  sumNNN += cos(theta - net->get_angle(col + 1, row - 1, layer));
  sumNNN += cos(theta - net->get_angle(col - 1, row - 1, layer));
  return sumNN + sumNNN * decay;
}

double Physics::local_kinetic_energy(int col, int row, int layer) {
  double w = net->get_angular_velocity(col, row, layer);
  return w * w;
}
