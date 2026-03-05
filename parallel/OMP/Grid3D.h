#ifndef GRID3D_H_

#define GRID3D_H_

class Grid3D {
  private:
    double ***grid;
    const int cols;
    const int rows;
    const int layers;
  
    void allocate();
    int periodic_index( int max, int idx );

  public:

    Grid3D( int rows, int cols, int layers );

    int get_cols() {
      return cols;
    }
    int get_rows() {
      return rows;
    }
    int get_layers() {
      return layers;
    }
    double get(int col, int row, int layer );
    void set( int col, int row, int layer, double value );
};

#endif