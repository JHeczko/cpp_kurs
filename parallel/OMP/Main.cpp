
#include <iomanip>
#include <iostream>
#include <random>

#include "Net.h"
#include "SequentialSimulation.h"
#include "Simulation.h"

#ifdef _OPENMP
#include "ParallelSimulation.h"
#endif

using namespace std;

void initialize_net(Net *net, int cols, int rows, int layers);
void simulation(Simulation *sim, Net *net, int steps, int energy_report_every,
                int state_report_every, double angle, int bins);

int main(int args, char **argv) {

  double J = 1.0;
  double I = 1.0;
  double decay = 0.5;
  double dt = 0.025;

  int layers = 100;
  int cols = 50;
  int rows = 50;
  int steps = 1000;
  int energy_report_every = 25;
  int state_report_every = 50;
  double angle = 1.6;
  int bins = 11;

  Net *net = new Net(cols, rows, layers);

  #ifdef _OPENMP
    Simulation *sim = new ParallelSimulation(net, I, J, decay, dt);
  #else
    Simulation *sim = new SequentialSimulation(net, I, J, decay, dt);
  #endif

  initialize_net(net, cols, rows, layers);

  simulation(sim, net, steps, energy_report_every, state_report_every, angle,
             bins);
}




void initialize_net(Net *net, int cols, int rows, int layers) {
  mt19937_64 rng(1234);
  uniform_real_distribution<double> unif(-0.3, 0.3);

  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angle(col, row, layer, 0);
        net->set_angular_velocity(col, row, layer, 0);
      }

  int col_m = cols / 2;
  int row_m = rows / 2;
  int layer_m = layers / 2;

  int delta = cols;
  if (rows < delta)
    delta = rows;
  if (layers < delta)
    delta = layers;

  delta /= 4;

  int counter = 0;
  for (int layer = layer_m - delta; layer <= layer_m + delta; layer++)
    for (int row = row_m - delta; row <= row_m + delta; row++)
      for (int col = col_m - delta; col <= col_m + delta; col++) {
        net->set_angle(col, row, layer, 1.6);
        counter++;
      }

  int all = cols * rows * layers;
  cout << "Zmieniono kierunek " << counter << " magnesow" << endl;
  cout << "Wszystkie magnesy  " << all << endl;
  cout << "Co daje            " << (100.0 * counter) / all << "%" << endl;
}




void simulation(Simulation *sim, Net *net, int steps, int energy_report_every, int state_report_every, double angle, int bins) {
  double Epot, Ekin, Etot;

  double *histogram = new double[bins];
  double *histogram0 = new double[bins];

  cout << fixed << endl;

  for (int step = 0; step < steps; step += energy_report_every) {

    if (step % energy_report_every == 0) {
      Epot = sim->total_potential_energy();
      Ekin = sim->total_kinetic_energy();
      Etot = Epot + Ekin;
      cout << "step " << step << " Epot = " << Epot << " Ekin = " << Ekin << " total = " << Etot << endl;
    }

    if (step % state_report_every == 0) {
      cout << "step " << step << " angle = " << net->get_angle(0, 0, 0) << " w = " << net->get_angular_velocity(0, 0, 0) << endl;

      sim->correlation(histogram, bins, angle);
      sim->correlation(histogram0, bins, 0.0);

      for (int bin = 0; bin < bins; bin++){
        cout << "h[ " << setw(2) << bin << " ] = " << histogram[bin] << " " << histogram0[bin] << endl;
      }
      
      cout << "self_correlation   " << sim->self_correlation() << endl;
    }

    sim->simulation(energy_report_every);
  } // for
} // simulation