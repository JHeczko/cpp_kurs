#ifndef PAR_SIMULATION_H_

#define PAR_SIMULATION_H_

#include "Simulation.h"
// #include <iostream>
// #include <iomanip>


class  ParallelSimulation: public Simulation {

  // Net *const net;
  // Physics *const physics;
  // const double dt;
  // const double reduced_time;
  // const double I;
  // const double J;
private:
  int rows, cols, layers;
  int rank,size;
  int rows_from, rows_to, cols_from, cols_to, layers_from, layers_to;
  
  char split;
  
  // zmienne do uzytku tylko w procesie 0;
  double total_kinetic_energy_gathered;
  double total_potential_energy_gathered;

  void angular_valocity_half_step();
  void new_angle();
  void update_angular_velocity();
  void single_simulation_step();

  void get_border_values();

//   void print_borders(){
//     std::cout << "Jestem proces " << this->rank << ":" << "\nCols: "<< this->cols_from << ":" << this->cols_to << "\nRows: "<< this->rows_from << ":" << this->rows_to << "\nLayers: "<< this->layers_from << ":" << this->layers_to << std::endl;
//   };
//   void print_net(){
//     int rank = this->rank;
//     int cols_from = this->cols_from-1;
//     int cols_to = this->cols_to + 1;
//     int rows_from = this->rows_from;
//     int rows_to = this->rows_to;
//     int layers_from = this->layers_from;
//     int layers_to = this->layers_to;

//     std::cout << "=============================================\n";
//     std::cout << "Proces " << rank << " (Net dump)\n";
//     std::cout << "Zakres: "
//               << "layers[" << this->layers_from << ":" << this->layers_to << "], "
//               << "rows[" << this->rows_from << ":" << this->rows_to << "], "
//               << "cols[" << this->cols_from << ":" << this->cols_to << "]\n";
//     std::cout << "=============================================\n\n";

//     // ===== ANGULAR VELOCITY =====
//     std::cout << "Angular Velocity (ω):\n    ";
//     for (int c = cols_from; c <= cols_to; ++c)
//         std::cout << std::setw(10) << c;
//     std::cout << "\n";

//     for (int r = rows_from; r <= rows_to; ++r) {
//         std::cout << std::setw(3) << r << " ";
//         for (int c = cols_from; c <= cols_to; ++c) {
//             std::cout << "(";
//             for (int l = layers_from; l <= layers_to; ++l) {
//                 std::cout << std::fixed << std::setprecision(2)
//                           << this->net->get_angular_velocity(c, r, l);
//                 if (l < layers_to) std::cout << ", ";
//             }
//             std::cout << ")";
//             std::cout << std::setw(3);
//         }
//         std::cout << "\n";
//     }

//     std::cout << "\nAngles (θ):\n    ";
//     for (int c = cols_from; c <= cols_to; ++c)
//         std::cout << std::setw(10) << c;
//     std::cout << "\n";

//     for (int r = rows_from; r <= rows_to; ++r) {
//         std::cout << std::setw(3) << r << " ";
//         for (int c = cols_from; c <= cols_to; ++c) {
//             std::cout << "(";
//             for (int l = layers_from; l <= layers_to; ++l) {
//                 std::cout << std::fixed << std::setprecision(2)
//                           << this->net->get_angle(c, r, l);
//                 if (l < layers_to) std::cout << ", ";
//             }
//             std::cout << ")";
//             std::cout << std::setw(3);
//         }
//         std::cout << "\n";
//     }

//     std::cout << "---------------------------------------------\n\n";
// }
//   void print_whole_net(){
//      // drukujemy tylko na proc. 0 (zakładamy, że wcześniej wywołano
//     // angles_and_velocities_to_proc_0(), żeby proc 0 miał cały net)
//     if (this->rank != 0) return;

//     for (int layer = 0; layer < this->layers; ++layer) {
//         std::cout << "Layer " << layer << ":\n";

//         for (int row = 0; row < this->rows; ++row) {
//             for (int col = 0; col < this->cols; ++col) {
//                 double angle = this->net->get_angle(col, row, layer);
//                 double vel = this->net->get_angular_velocity(col, row, layer);
//                 std::cout << "(" << angle << "," << vel << ") ";
//             }
//             std::cout << std::endl;
//         }
//         std::cout << std::endl;
//     }
// }


public:
  ParallelSimulation(Net *const _net, double _I, double _J, double _decay, double _dt);

  //  metoda zostanie wykonana we wszystkich procesach - zleca wykonanie steps kroków symulacji
  void simulation( int steps );
  
  // metoda zostanie wykonana przez proces 0 - zwraca całkowitą energię kinetyczną.
  double total_potential_energy();

  // metoda zostanie wykonana przez proces 0 - zwraca całkowitą energię potencjalną.
  double total_kinetic_energy();

  // metoda zostanie wykonana we wszystkich procesach przed pobraniem całkowitej energii potencjalnej i kinetycznej
  void calc_energy();

  // metoda zostanie wykonana we wszystkich procesach przed pierwszym krokiem symulacji
  void initialize();

  // metoda zostanie wykonana we wszystkich procesach. Po jej zakończeniu w procesie o numerze 0 mają być dostępne do odczytu aktualne kąty i prędkości kątowe magnesów.
  void angles_and_velocities_to_proc_0();

};

#endif
