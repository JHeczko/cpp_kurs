#include "Grid3D.h"

Grid3D::Grid3D( int cols, int rows, int layers ) : 
 cols( cols ), rows( rows ), layers( layers ) {
  allocate();
 }

void Grid3D::allocate() {
  grid = new double **[layers];

  for (int layer = 0; layer < layers; layer++) {
    grid[layer] = new double *[rows];
    for (int row = 0; row < rows; row++)
      grid[layer][row] = new double[cols];
  }
}

int Grid3D::periodic_index(int max, int idx) {
  return ((idx % max) + max) % max;
}

double Grid3D::get(int col, int row, int layer) {
  return grid[periodic_index(layers, layer)][periodic_index(rows, row)]
             [periodic_index(cols, col)];
}

void Grid3D::set(int col, int row, int layer, double value) {
  grid[periodic_index(layers, layer)][periodic_index(rows, row)]
      [periodic_index(cols, col)] = value;
}