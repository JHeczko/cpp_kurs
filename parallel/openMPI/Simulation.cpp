#include "Simulation.h"
#include <iostream>

using namespace std;

Simulation::Simulation(Net *const _net, double _I, double _J, double _decay, double _dt): net(_net), dt(_dt), I(_I), J(_J), physics(new Physics(_net, _decay)),reduced_time(-_J * 0.5 * dt / _I) {
};