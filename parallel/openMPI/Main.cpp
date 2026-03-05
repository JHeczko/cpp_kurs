#include <iostream>
#include <random>

#include "Net.h"
#include "Simulation.h"
#include "SequentialSimulation.h"

#define MPI_ON

#ifdef MPI_ON
  #include "ParallelSimulation.h"
  #include <mpi.h>
#endif

//using namespace std;

void initialize_net( Net *net, int cols, int rows, int layers );
void simulation( Simulation *sim, Net *net, int steps, int energy_report_every,int state_report_every, int rank  );

int main(int args, char **argv) {

  double J = 1.0;
  double I = 1.0;
  double decay = 0.5;
  double dt = 0.05;

  // l = 10
  // c = 50
  // r = 50
  int layers = 3;
  int cols = 40;
  int rows = 40;
  int steps = 1000;
  int energy_report_every = 25;
  int state_report_every = 100;

  int rank = 0;

// standardowa inicjalizacja MPI
#ifdef MPI_ON
  MPI_Init(&args, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank == 0) std::cout << "MPI version " << MPI_VERSION << std::endl;
#endif

  // kazdy proces ma siatke, tych samych rozmiarow
  Net *net = new Net(cols, rows, layers);

#ifdef MPI_ON
  Simulation *sim = new ParallelSimulation(net, I, J, decay, dt);
#else
  Simulation *sim = new SequentialSimulation(net, I, J, decay, dt);
#endif

  // tylko proces o numerze 0, MOZE zainicjalizowac siatke nowymi wartosciami
  if ( rank == 0 ) {
    initialize_net( net, cols, rows, layers );
  }

  // tutaj nastepuje rozeslanie wartosci, odpowiednich danej siatce do calej reszty
  sim->initialize();

  simulation( sim, net, steps, energy_report_every, state_report_every, rank );

#ifdef MPI_ON
  MPI_Finalize();
#endif
  if(rank == 0) std::cout << "KONIEC" << std::endl;
}


void initialize_net( Net *net, int cols, int rows, int layers ) {
  std::mt19937_64 rng(1234);
  std::uniform_real_distribution<double> unif(-0.3, 0.3);

  // siatka glowna inicjalizowana 0
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        net->set_angle(col, row, layer, row*col);
        net->set_angular_velocity(col, row, layer, row*col);
      }

  // poza tutaj komorka, bo musimy jakos wprawic w ruch te magnesy
  for (int row = 2; row < 6; row++)
    for (int col = 2; col < 6; col++) {
      net->set_angle(col, row, 1, 1.67);
    }
}






void simulation( Simulation *sim, Net *net, int steps, int energy_report_every,int state_report_every, int rank  ) {

  double Epot, Ekin, Etot;

  for (int step = 0; step < steps; step++) {

    // tutaj jest tak naprawde printowanie
    if ( step % energy_report_every == 0 ) {
      sim->calc_energy();
      if ( rank == 0 ) {
        Epot = sim->total_potential_energy();
        Ekin = sim->total_kinetic_energy();
        Etot = Epot + Ekin;
        std::cout << "step " << step << " Epot = " << Epot << " Ekin = " << Ekin << " total = " << Etot << std::endl;
      }
    }

    // tutaj jest tak naprawde printowanie
    if ( step % state_report_every == 0 ) {
      sim->angles_and_velocities_to_proc_0();
      if ( rank == 0 ) {
        std::cout << "step " << step << " angle = " << net->get_angle(0,0,0) << " w = " <<  net->get_angular_velocity(0,0,0) << std::endl;
      }
    }

    // w zasadzie glowny krok symulazcji, tutaj wszystko jest liczone
    sim->simulation( energy_report_every );
  }
}

