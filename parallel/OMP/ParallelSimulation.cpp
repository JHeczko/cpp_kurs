#ifdef _OPENMP


#include "ParallelSimulation.h"
#include "Simulation.h"
#include <math.h>
#include <vector>
#include <omp.h>


ParallelSimulation::ParallelSimulation(Net *const _net, double _I, double _J, double _decay, double _dt) : Simulation(_net, _I, _J, _decay, _dt) {
  cols = net->get_cols();
  rows = net->get_rows();
  layers = net->get_layers();
}

// done
double ParallelSimulation::total_potential_energy() {
  double result = 0;

  #pragma omp parallel for reduction(+:result) collapse(3) schedule(static)
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++) {
        result += physics->local_potential_energy(col, row, layer);
      }
  return -J * 0.5 * result;

}

// done
double ParallelSimulation::total_kinetic_energy() {
  double result = 0;
  
  #pragma omp parallel for reduction(+:result) collapse(3) schedule(static)
  for (int layer = 0; layer < layers; layer++)
    for (int row = 0; row < rows; row++)
      for (int col = 0; col < cols; col++){
        result += physics->local_kinetic_energy(col, row, layer);
      }
  
  return 0.5 * I * result;
}

// done
void ParallelSimulation::simulation(int steps) {
  for (int i = 0; i < steps; i++){
    single_simulation_step();
  }
}

// done
void ParallelSimulation::single_simulation_step() {
  angular_valocity_half_step();
  new_angle();
  angular_valocity_half_step();
}

// done
void ParallelSimulation::angular_valocity_half_step() {
  #pragma omp parallel for collapse(3) schedule(static)
  for (int layer = 0; layer < layers; layer++) {
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        net->set_angular_velocity(col, row, layer, net->get_angular_velocity(col, row, layer) + reduced_time * physics->torque(col, row, layer));
      }
    }
  }
}

//done
void ParallelSimulation::new_angle() {
  #pragma omp parallel for collapse(3) schedule(static)
  for (int layer = 0; layer < layers; layer++){
    for (int row = 0; row < rows; row++){
      for (int col = 0; col < cols; col++) {
        net->set_angle(col, row, layer, net->get_angle(col, row, layer) + dt * net->get_angular_velocity(col, row, layer));
      }
    }
  }
}



// done - do testu
void ParallelSimulation::correlation(double *histogram, int bins, double angle) {
    double toBin = bins / 2.0;
    int nthreads = omp_get_max_threads();

    #pragma omp parallel for
    for (int i = 0; i < bins; i++) {
        histogram[i] = 0.0;
    }

    std::vector<std::vector< double>> local_hist(nthreads, std::vector<double>(bins, 0.0));

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        auto &h = local_hist[tid];

        #pragma omp for collapse(3) nowait schedule(static)
        for (int layer = 0; layer < layers; layer++) {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    int idx = (int)((cos(angle - net->get_angle(col, row, layer)) + 1.0) * toBin) % bins;
                    h[idx] += 1.0;
                }
            }
        }
    }

    // Redukcja histogramów
    #pragma omp parallel for
    for (int bin = 0; bin < bins; bin++) {
        for (int t = 0; t < nthreads; t++) {
            histogram[bin] += local_hist[t][bin];
        }
    }

    double vol = cols * rows * layers;

    #pragma omp parallel for
    for (int bin = 0; bin < bins; bin++) {
        histogram[bin] /= vol;
    }
}



// done - do testu
double ParallelSimulation::self_correlation() {
  double sum = 0.0;

  #pragma omp parallel for reduction(+:sum) collapse(3)
  for (int layer = 1; layer < layers - 1; layer++){
    for (int row = 1; row < rows - 1; row++){
      for (int col = 1; col < cols - 1; col++) {
        double angle = net->get_angle(col, row, layer);
        sum += cos(angle - net->get_angle(col + 1, row, layer));
        sum += cos(angle - net->get_angle(col - 1, row, layer));
        sum += cos(angle - net->get_angle(col, row + 1, layer));
        sum += cos(angle - net->get_angle(col, row - 1, layer));
        sum += cos(angle - net->get_angle(col, row, layer + 1));
        sum += cos(angle - net->get_angle(col, row, layer - 1));
      }
    }
  }

  double vol = 6 * (cols - 2) * (rows - 2) * (layers - 2);

  return sum / vol;
}


#endif