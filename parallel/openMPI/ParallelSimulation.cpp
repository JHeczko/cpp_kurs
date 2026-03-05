#include "Simulation.h"
#include "ParallelSimulation.h"
#include <mpi.h>
#include <algorithm>


void ParallelSimulation::initialize(){
  int size = this->size;
  //int size_true = this->size;
  int cols = this->net->get_cols();
  int rows = this->net->get_rows();
  int layers = this->net->get_layers();
  
  int column_split = (layers * rows);
  int row_split = (layers * cols);
  int layer_split = (cols * rows);
  
  int best_split = std::min({column_split, row_split, layer_split});

  if (best_split == column_split){
    this->split = 'C';
  }else if (best_split == row_split){
    this->split = 'R';
  }else if (best_split == layer_split){
    this->split = 'L';
  }
    
  #ifdef DEBUG
  std::cout << "[DEBUG] Optymalny split po " << this->split << " : " << column_split << ":" << row_split << ":" << layer_split << std::endl; 
  #endif

  //tworzenie podzialu i rozsyl do innych procesow
  if(this->rank == 0){

  
    /**
     * Uwaga !!!!
     * Tutaj ta logika ograniczania obliczen do kilku procesow jak za duzo jest naiwna i nie dziala poprawnie
     * 
     * Te procesy tam dalej sa w tle i beda zaburzaly obliczenia(albo i nie, ale lepiej porpawic jesli bedzie konieczne)
     */


    if(best_split == column_split){
      // jezeli jest za duzo procesow, to wylaczamy wtedy obliczenia na niekotrych z nich
      // if (size > cols){
      //   size = cols;
      // }else{
      //   size=size_true;
      // }

      //split co C

      int step = (cols/size)-1; 
      int rest_cnt = cols%size;

      // aktualizacja pozycji dla procesu 0
      this->cols_from = 0;
      this->cols_to = this->cols_from+step;
      if (rest_cnt != 0){
        this->cols_to++;
        rest_cnt--;
      }

      this->rows_from = 0;
      this->rows_to = rows-1;
      this->layers_from = 0;
      this->layers_to = layers-1;


      // aktualizacja pozycji dla reszty
      int tosend_rows_from, tosend_rows_to;
      int tosend_cols_from, tosend_cols_to;
      int tosend_layers_from, tosend_layers_to;

      tosend_rows_from = 0;
      tosend_rows_to = rows-1;
      tosend_layers_from = 0;
      tosend_layers_to = layers-1;

      int prev_index = this->cols_to;
      for (int dest_rank=1; dest_rank < size; ++dest_rank){
        tosend_cols_from = prev_index+1;
        tosend_cols_to = tosend_cols_from+step;

        if (rest_cnt != 0){
          tosend_cols_to++;
          rest_cnt--;
        };


        prev_index = tosend_cols_to;
        
        // ======= pakowanie i wysyalnie indexow
        int buf_tosend[6] = {tosend_rows_from, tosend_rows_to, 
                              tosend_cols_from, tosend_cols_to, 
                              tosend_layers_from, tosend_layers_to};
        MPI_Send(buf_tosend, 6, MPI_INT, dest_rank, dest_rank, MPI_COMM_WORLD);


        // ======= pakowanie i wysylanie danych
        int rows_count = tosend_rows_to - tosend_rows_from + 1;
        int cols_count = tosend_cols_to - tosend_cols_from + 1;
        int layers_count = tosend_layers_to - tosend_layers_from + 1;
        int block_size = rows_count * cols_count * layers_count;

        std::vector<double> buffer(block_size);

        // ====== WYSYŁANIE ANGLE ======
        int idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = this->net->get_angle(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 1, MPI_COMM_WORLD);

        // ====== WYSYŁANIE ANGULAR VELOCITY ======
        idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = net->get_angular_velocity(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 2, MPI_COMM_WORLD);
      }



    }else if (best_split == row_split){
      // jezeli jest za duzo procesow, to wylaczamy wtedy obliczenia na niekotrych z nich
      // if (size > rows){
      //   size = rows;
      // }else{
      //   size=size_true;
      // }

      //split co R

      int step = (rows/size)-1; 
      int rest_cnt = rows%size;

      // aktualizacja pozycji dla procesu 0
      this->rows_from = 0;
      this->rows_to = this->rows_from+step;
      if (rest_cnt != 0){
        this->rows_to++;
        rest_cnt--;
      }

      this->cols_from = 0;
      this->cols_to = cols-1;
      this->layers_from = 0;
      this->layers_to = layers-1;


      // aktualizacja pozycji dla reszty
      int tosend_rows_from, tosend_rows_to;
      int tosend_cols_from, tosend_cols_to;
      int tosend_layers_from, tosend_layers_to;

      tosend_cols_from = 0;
      tosend_cols_to = cols-1;
      tosend_layers_from = 0;
      tosend_layers_to = layers-1;

      int prev_index = this->rows_to;
      for (int dest_rank=1; dest_rank < size; ++dest_rank){
        tosend_rows_from = prev_index+1;
        tosend_rows_to = tosend_rows_from+step;

        if (rest_cnt != 0){
          tosend_rows_to++;
          rest_cnt--;
        };


        prev_index = tosend_rows_to;
        
        // pakowanie i wysyalnie indexow
        int buf_tosend[6] = {tosend_rows_from, tosend_rows_to, tosend_cols_from, tosend_cols_to, tosend_layers_from, tosend_layers_to};
        MPI_Send(buf_tosend, 6, MPI_INT, dest_rank, dest_rank, MPI_COMM_WORLD);

        // ======= pakowanie i wysylanie danych
        int rows_count = tosend_rows_to - tosend_rows_from + 1;
        int cols_count = tosend_cols_to - tosend_cols_from + 1;
        int layers_count = tosend_layers_to - tosend_layers_from + 1;
        int block_size = rows_count * cols_count * layers_count;

        std::vector<double> buffer(block_size);

        // ====== WYSYŁANIE ANGLE ======
        int idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = this->net->get_angle(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 1, MPI_COMM_WORLD);

        // ====== WYSYŁANIE ANGULAR VELOCITY ======
        idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = net->get_angular_velocity(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 2, MPI_COMM_WORLD);
      }


    }else if (best_split == layer_split){
      // jezeli jest za duzo procesow, to wylaczamy wtedy obliczenia na niekotrych z nich
      // if (size > layers){
      //   size = layers;
      // }else{
      //   size=size_true;
      // }

      //split co L

      int step = (layers/size)-1; 
      int rest_cnt = layers%size;

      // aktualizacja pozycji dla procesu 0
      this->layers_from = 0;
      this->layers_to = this->layers_from+step;
      if (rest_cnt != 0){
        this->layers_to++;
        rest_cnt--;
      }

      this->cols_from = 0;
      this->cols_to = cols-1;
      this->rows_from = 0;
      this->rows_to = rows-1;

      // aktualizacja pozycji dla reszty
      int tosend_rows_from, tosend_rows_to;
      int tosend_cols_from, tosend_cols_to;
      int tosend_layers_from, tosend_layers_to;

      tosend_cols_from = 0;
      tosend_cols_to = cols-1;
      tosend_rows_from = 0;
      tosend_rows_to = rows-1;

      int prev_index = this->layers_to;
      for (int dest_rank=1; dest_rank < size; ++dest_rank){
        tosend_layers_from = prev_index+1;
        tosend_layers_to = tosend_layers_from+step;

        if (rest_cnt != 0){
          tosend_layers_to++;
          rest_cnt--;
        };


        prev_index = tosend_layers_to;
        
        // pakowanie i wysyalnie
        int buf_tosend[6] = {tosend_rows_from, tosend_rows_to, tosend_cols_from, tosend_cols_to, tosend_layers_from, tosend_layers_to};
        MPI_Send(buf_tosend, 6, MPI_INT, dest_rank, dest_rank, MPI_COMM_WORLD);


        // ======= pakowanie i wysylanie danych
        int rows_count = tosend_rows_to - tosend_rows_from + 1;
        int cols_count = tosend_cols_to - tosend_cols_from + 1;
        int layers_count = tosend_layers_to - tosend_layers_from + 1;
        int block_size = rows_count * cols_count * layers_count;

        std::vector<double> buffer(block_size);

        // ====== WYSYŁANIE ANGLE ======
        int idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = this->net->get_angle(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 1, MPI_COMM_WORLD);

        // ====== WYSYŁANIE ANGULAR VELOCITY ======
        idx = 0;
        for (int l = tosend_layers_from; l <= tosend_layers_to; ++l)
            for (int r = tosend_rows_from; r <= tosend_rows_to; ++r)
                for (int c = tosend_cols_from; c <= tosend_cols_to; ++c)
                    buffer[idx++] = net->get_angular_velocity(c, r, l);

        MPI_Send(buffer.data(), block_size, MPI_DOUBLE, dest_rank, 2, MPI_COMM_WORLD);
      }
    }
  }

  // odebranie info z procesu 0
  if (this->rank != 0){
    int recv_indexs[6];

    MPI_Recv(recv_indexs, 6, MPI_INT, 0, this->rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    this->rows_from = recv_indexs[0];
    this->rows_to = recv_indexs[1];
    this->cols_from = recv_indexs[2];
    this->cols_to = recv_indexs[3];
    this->layers_from = recv_indexs[4];
    this->layers_to = recv_indexs[5];

    int rows_count = this->rows_to - this->rows_from   + 1;
    int cols_count = this->cols_to - this->cols_from   + 1;
    int layers_count = this->layers_to - this->layers_from + 1;
    int block_size = rows_count * cols_count * layers_count;

    std::vector<double> buffer(block_size);

    // ====== ODBIERZ ANGLE ======
    MPI_Recv(buffer.data(), block_size, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int idx = 0;
    for (int l = layers_from; l <= layers_to; ++l)
        for (int r = rows_from; r <= rows_to; ++r)
            for (int c = cols_from; c <= cols_to; ++c)
                net->set_angle(c, r, l, buffer[idx++]);

    // ====== ODBIERZ ANGULAR VELOCITY ======
    MPI_Recv(buffer.data(), block_size, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    idx = 0;
    for (int l = layers_from; l <= layers_to; ++l)
        for (int r = rows_from; r <= rows_to; ++r)
            for (int c = cols_from; c <= cols_to; ++c)
                net->set_angular_velocity(c, r, l, buffer[idx++]);
  }


  #ifdef DEBUG
    const int TAG = 42;
    int token = 0;

    if (this->rank != 0) {
        // czekaj na sygnał od poprzednika
        MPI_Recv(&token, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    this->get_border_values();

    if (rank != size - 1) {
        // daj sygnał następnemu procesowi
        MPI_Send(&token, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
  #endif
  
};

ParallelSimulation::ParallelSimulation(Net *const _net, double _I, double _J, double _decay, double _dt):Simulation( _net, _I, _J, _decay, _dt ) {
    this->cols = net->get_cols();
    this->rows = net->get_rows();
    this->layers = net->get_layers();
    MPI_Comm_rank(MPI_COMM_WORLD, &this->rank);
    MPI_Comm_size(MPI_COMM_WORLD, &this->size);
  }

double ParallelSimulation::total_potential_energy() {
  // double result = 0;
  // for (int layer = 0; layer < layers; layer++)
  //   for (int row = 0; row < rows; row++)
  //     for (int col = 0; col < cols; col++) {
  //       result += physics->local_potential_energy(col, row, layer);
  //     }
  // return -J * 0.5 * result;
  return this->total_potential_energy_gathered;
}

double ParallelSimulation::total_kinetic_energy() {
  // double result = 0;
  // for (int layer = 0; layer < layers; layer++)
  //   for (int row = 0; row < rows; row++)
  //     for (int col = 0; col < cols; col++){
  //       result += physics->local_kinetic_energy(col, row, layer);
  //     }
  // return 0.5 * I * result;
  return this->total_kinetic_energy_gathered;
}

void ParallelSimulation::calc_energy(){
  get_border_values();  

  // kinetic energy calculating
  double result_kinetic = 0;
  for (int layer = this->layers_from; layer <= this->layers_to; layer++)
    for (int row = this->rows_from; row <= this->rows_to; row++)
      for (int col = this->cols_from; col <= this->cols_to; col++){
        result_kinetic += physics->local_kinetic_energy(col, row, layer);
      }
  const double final_result_kinetic = 0.5 * I * result_kinetic;

  // potential energy calculating
  double result_potential = 0;
  for (int layer = this->layers_from; layer <= this->layers_to; layer++)
    for (int row = this->rows_from; row <= this->rows_to; row++)
      for (int col = this->cols_from; col <= this->cols_to; col++){
        result_potential += physics->local_potential_energy(col, row, layer);
      }
  const double final_result_potential = -J * 0.5 * result_potential;

  double tmp_kinetic;
  double tmp_potential;

  MPI_Reduce(
      &final_result_kinetic,                // lokalna wartość
      &tmp_kinetic, // wynik tylko w rank 0
      1,
      MPI_DOUBLE,
      MPI_SUM,
      0,
      MPI_COMM_WORLD
  );

  MPI_Reduce(
      &final_result_potential,
      &tmp_potential,
      1,
      MPI_DOUBLE,
      MPI_SUM,
      0,
      MPI_COMM_WORLD
  );

  if(rank == 0){
    this->total_kinetic_energy_gathered = tmp_kinetic;
    this->total_potential_energy_gathered = tmp_potential;
  }
}

void ParallelSimulation::simulation( int steps ) {
  for ( int i = 0; i < steps; i++ )
    single_simulation_step();
}

void ParallelSimulation::single_simulation_step() {
  get_border_values();  
  //MPI_Barrier(MPI_COMM_WORLD);
  angular_valocity_half_step();

  //get_border_values();  
  //MPI_Barrier(MPI_COMM_WORLD);
  new_angle();
  
  get_border_values();
  //MPI_Barrier(MPI_COMM_WORLD);
  update_angular_velocity();
}

void ParallelSimulation::angular_valocity_half_step() {
  for (int layer = this->layers_from; layer <= this->layers_to; layer++)
    for (int row = this->rows_from; row <= this->rows_to; row++)
      for (int col = this->cols_from; col <= this->cols_to; col++) {
        net->set_angular_velocity(
            col, row, layer,
            net->get_angular_velocity(col, row, layer) + reduced_time * physics->torque(col, row, layer));
      }
}

void ParallelSimulation::new_angle() {
  for (int layer = this->layers_from; layer <= this->layers_to; layer++)
    for (int row = this->rows_from; row <= this->rows_to; row++)
      for (int col = this->cols_from; col <= this->cols_to; col++) {
        net->set_angle(
            col, row, layer,
            net->get_angle(col, row, layer) + dt * net->get_angular_velocity(col, row, layer));
      }
}

void ParallelSimulation::update_angular_velocity() {
  for (int layer = this->layers_from; layer <= this->layers_to; layer++)
    for (int row = this->rows_from; row <= this->rows_to; row++)
      for (int col = this->cols_from; col <= this->cols_to; col++) {
        net->set_angular_velocity(
            col, row, layer,
            net->get_angular_velocity(col, row, layer) + reduced_time * physics->torque(col, row, layer));
      }
}

void ParallelSimulation::angles_and_velocities_to_proc_0() {
    int world_size = this->size;
    int world_rank = this->rank;

    //MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    //MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // ===== 1. każdy proces pakuje swoje dane =====
    int block_layers = this->layers_to - this->layers_from + 1;
    int block_rows   = this->rows_to   - this->rows_from   + 1;
    int block_cols   = this->cols_to   - this->cols_from   + 1;
    int block_size = block_layers * block_rows * block_cols;

    std::vector<double> angles_buf(block_size);
    std::vector<double> velocities_buf(block_size);

    #ifdef DEBUG
      const int TAG = 42;
      int token = 0;

      if (this->rank != 0) {
          // czekaj na sygnał od poprzednika
          MPI_Recv(&token, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }

      std::cout << "[DEBUG] Proces " << world_rank << " na " << world_size << "\nStaty bloku angles_and_velocities_to_proc_0:\n -layers: " << block_layers << " -rows: " << block_rows << " -cols: " << block_cols << " -block_size: " << block_size;

      if (rank != size - 1) {
          // daj sygnał następnemu procesowi
          MPI_Send(&token, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
      }

      MPI_Barrier(MPI_COMM_WORLD);
    #endif

    int idx = 0;
    for (int l = this->layers_from; l <= this->layers_to; ++l)
        for (int r = this->rows_from; r <= this->rows_to; ++r)
            for (int c = this->cols_from; c <= this->cols_to; ++c) {
                angles_buf[idx] = this->net->get_angle(c, r, l);
                velocities_buf[idx] = this->net->get_angular_velocity(c, r, l);
                idx++;
            }

    int ranges[6] = {this->rows_from, this->rows_to,
                     this->cols_from, this->cols_to,
                     this->layers_from, this->layers_to};

    // ===== 2. jeśli to nie jest proces 0 → wysyła =====
    if (world_rank != 0) {
        // ===== 1. każdy proces pakuje swoje dane =====
        int block_layers = this->layers_to - this->layers_from + 1;
        int block_rows   = this->rows_to   - this->rows_from   + 1;
        int block_cols   = this->cols_to   - this->cols_from   + 1;
        int block_size = block_layers * block_rows * block_cols;

        std::vector<double> angles_buf(block_size);
        std::vector<double> velocities_buf(block_size);

        int idx = 0;
        for (int l = this->layers_from; l <= this->layers_to; ++l)
            for (int r = this->rows_from; r <= this->rows_to; ++r)
                for (int c = this->cols_from; c <= this->cols_to; ++c) {
                    angles_buf[idx] = this->net->get_angle(c, r, l);
                    velocities_buf[idx] = this->net->get_angular_velocity(c, r, l);
                    idx++;
                }

        int ranges[6] = {this->rows_from, this->rows_to,
                        this->cols_from, this->cols_to,
                        this->layers_from, this->layers_to};

        // std::cout << "Angles for " << world_rank << ": "<< std::endl;
        // for (double x : angles_buf){
        //   std::cout << x << ", ";
        // }
        // std::cout << std::endl;

        // std::cout << "Vel for " << world_rank << ": "<< std::endl;
        // for (double x : velocities_buf){
        //   std::cout << x << ", ";
        // }
        // std::cout << std::endl;
        
        //===== 2. jeśli to nie jest proces 0 → wysyła =====
        
        MPI_Send(ranges, 6, MPI_INT, 0, 100 + world_rank, MPI_COMM_WORLD);
        MPI_Send(angles_buf.data(), block_size, MPI_DOUBLE, 0, 200 + world_rank, MPI_COMM_WORLD);
        MPI_Send(velocities_buf.data(), block_size, MPI_DOUBLE, 0, 300 + world_rank, MPI_COMM_WORLD);

    }


    // ===== 3. proces 0 odbiera wszystkie dane =====
    if(world_rank == 0){
      for (int src = 1; src < world_size; ++src) {
          int recv_ranges[6];
          MPI_Recv(recv_ranges, 6, MPI_INT, src, 100 + src, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          int r_from = recv_ranges[0];
          int r_to   = recv_ranges[1];
          int c_from = recv_ranges[2];
          int c_to   = recv_ranges[3];
          int l_from = recv_ranges[4];
          int l_to   = recv_ranges[5];

          int recv_layers = l_to - l_from + 1;
          int recv_rows   = r_to - r_from + 1;
          int recv_cols   = c_to - c_from + 1;
          int recv_size   = recv_layers * recv_rows * recv_cols;
          
          // std::cout << "src:" << src << " r_from=" << r_from << ", "
          // << "r_to="   << r_to   << ", "
          // << "c_from=" << c_from << ", "
          // << "c_to="   << c_to   << ", "
          // << "l_from=" << l_from << ", "
          // << "l_to="   << l_to   << std::endl;

          std::vector<double> recv_angles(recv_size);
          std::vector<double> recv_velocities(recv_size);

          // xd tutaj uwaga, bo jest wskaznik do wektora, nie modyfikujemy tak jak natura chciala ale przez wewnetrzna tablice
          MPI_Recv(recv_angles.data(), recv_size, MPI_DOUBLE, src, 200 + src, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Recv(recv_velocities.data(), recv_size, MPI_DOUBLE, src, 300 + src, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          // std::cout << "Angles for " << src << ": "<< std::endl;
          // for (double x : recv_angles){
          //   std::cout << x << ", ";
          // }
          // std::cout << std::endl;

          // std::cout << "Vel for " << src << ": "<< std::endl;
          // for (double x : recv_velocities){
          //   std::cout << x << ", ";
          // }
          // std::cout << std::endl;

          // ===== 4. proces 0 wstawia dane do globalnego neta =====
          int idx2 = 0;
          for (int l = l_from; l <= l_to; ++l)
              for (int r = r_from; r <= r_to; ++r)
                  for (int c = c_from; c <= c_to; ++c) {
                      this->net->set_angle(c, r, l, recv_angles[idx2]);
                      this->net->set_angular_velocity(c, r, l, recv_velocities[idx2]);
                      idx2++;
                  }
      }
    }

    //std::cout << "Szybki test: " << this->net->get_angle(13,13,0) << std::endl;
    // Proces 0 już ma wszystko — swoje i cudze

    //MPI_Barrier(MPI_COMM_WORLD);
}

void ParallelSimulation::get_border_values(){
  int rank_prev = (this->rank + this->size - 1) % this->size;
  int rank_next = (this->rank + this->size + 1) % this->size;

  int data_size;

  std::vector<double> recv_velocity_angles_left(0);
  std::vector<double> recv_velocity_angles_right(0);

  std::vector<double> sendv_velocity_angles_prev(0);
  std::vector<double> sendv_velocity_angles_next(0);

  // std::cout << "Rank " << this->rank 
  //           << " split=" << this->split 
  //           << " prev=" << rank_prev 
  //           << " next=" << rank_next 
  //           << std::endl;

  switch(this->split){
    case 'C': {
      //std::cout << "Witam po C" << std::endl;
      data_size = (this->rows * this->layers)*2;
      
      std::vector<double> recv_velocity_angles_left(data_size);
      std::vector<double> recv_velocity_angles_right(data_size);

      std::vector<double> sendv_velocity_angles_prev(data_size);
      std::vector<double> sendv_velocity_angles_next(data_size);

      // pakowanie do wysylko
      int idx = 0;
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          sendv_velocity_angles_prev[idx] = this->net->get_angular_velocity(this->cols_from, r, l);
          sendv_velocity_angles_next[idx] = this->net->get_angular_velocity(this->cols_to, r, l);
          ++idx;
        }
      
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          sendv_velocity_angles_prev[idx] = this->net->get_angle(this->cols_from, r, l);
          sendv_velocity_angles_next[idx] = this->net->get_angle(this->cols_to, r, l);
          ++idx;
        }

      // wysylanie swojej prawej scianki, oraz odbior lewej strony z procesu rank_prev 
      MPI_Sendrecv(sendv_velocity_angles_next.data(), data_size, MPI_DOUBLE, rank_next, 1000,
      recv_velocity_angles_left.data(), data_size, MPI_DOUBLE, rank_prev, 1000, 
      MPI_COMM_WORLD, MPI_STATUSES_IGNORE);


      // na odwrot wysylanie swojej lewej scianki i odbior jako prawa z procesu rank_next 
      MPI_Sendrecv(sendv_velocity_angles_prev.data(), data_size, MPI_DOUBLE, rank_prev, 2000, recv_velocity_angles_right.data(), data_size, MPI_DOUBLE, rank_next, 2000, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
      
      // odpakowanie do wysylko
      idx = 0;
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          this->net->set_angular_velocity(this->cols_from-1, r, l, recv_velocity_angles_left[idx]);
          this->net->set_angular_velocity(this->cols_to+1, r, l, recv_velocity_angles_right[idx]);
          ++idx;
        }
      
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          this->net->set_angle(this->cols_from-1, r, l, recv_velocity_angles_left[idx]);
          this->net->set_angle(this->cols_to+1, r, l, recv_velocity_angles_right[idx]);
          ++idx;
        }

      break;
    }
    case 'R': {
      //std::cout << "Witam po R" << std::endl;
      data_size = (this->cols * this->layers)*2;
      
      std::vector<double> recv_velocity_angles_left(data_size);
      std::vector<double> recv_velocity_angles_right(data_size);

      std::vector<double> sendv_velocity_angles_prev(data_size);
      std::vector<double> sendv_velocity_angles_next(data_size);

      // pakowanie do wysylko
      int idx = 0;
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int c = this->cols_from; c <= this->cols_to; ++c){
          sendv_velocity_angles_prev[idx] = this->net->get_angular_velocity(c, this->rows_from, l);
          sendv_velocity_angles_next[idx] = this->net->get_angular_velocity(c, this->rows_to, l);
          ++idx;
        }
      
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int c = this->cols_from; c <= this->cols_to; ++c){
          sendv_velocity_angles_prev[idx] = this->net->get_angle(c, this->rows_from, l);
          sendv_velocity_angles_next[idx] = this->net->get_angle(c, this->rows_to, l);
          ++idx;
        }

      // wysylanie swojej prawej scianki, oraz odbior lewej strony z procesu rank_prev 
      MPI_Sendrecv(sendv_velocity_angles_next.data(), data_size, MPI_DOUBLE, rank_next, 1000,
      recv_velocity_angles_left.data(), data_size, MPI_DOUBLE, rank_prev, 1000, 
      MPI_COMM_WORLD, MPI_STATUSES_IGNORE);


      // na odwrot wysylanie swojej lewej scianki i odbior jako prawa z procesu rank_next 
      MPI_Sendrecv(sendv_velocity_angles_prev.data(), data_size, MPI_DOUBLE, rank_prev, 2000, recv_velocity_angles_right.data(), data_size, MPI_DOUBLE, rank_next, 2000, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
      
      // odpakowanie do wysylko
      idx = 0;
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int c = this->cols_from; c <= this->cols_to; ++c){
          this->net->set_angular_velocity(c, this->rows_from-1, l, recv_velocity_angles_left[idx]);
          this->net->set_angular_velocity(c, this->rows_to+1, l, recv_velocity_angles_right[idx]);
          ++idx;
        }
      
      for(int l = this->layers_from; l <= this->layers_to; ++l)
        for(int c = this->cols_from; c <= this->cols_to; ++c){
          this->net->set_angle(c, this->rows_from-1, l, recv_velocity_angles_left[idx]);
          this->net->set_angle(c, this->rows_to+1, l, recv_velocity_angles_right[idx]);
          ++idx;
        }

      break;
    }
    case 'L':{ 
      //std::cout << "Witam po L" << std::endl;
      data_size = (this->rows * this->cols)*2;
      
      std::vector<double> recv_velocity_angles_left(data_size);
      std::vector<double> recv_velocity_angles_right(data_size);

      std::vector<double> sendv_velocity_angles_prev(data_size);
      std::vector<double> sendv_velocity_angles_next(data_size);

      // pakowanie do wysylko
      int idx = 0;
      for(int c = this->cols_from; c <= this->cols_to; ++c)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          sendv_velocity_angles_prev[idx] = this->net->get_angular_velocity(c, r, this->layers_from);
          sendv_velocity_angles_next[idx] = this->net->get_angular_velocity(c, r, this->layers_to);
          ++idx;
        }
      
      for(int c = this->cols_from; c <= this->cols_to; ++c)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          sendv_velocity_angles_prev[idx] = this->net->get_angle(c, r, this->layers_from);
          sendv_velocity_angles_next[idx] = this->net->get_angle(c, r, this->layers_to);
          ++idx;
        }

      // wysylanie swojej prawej scianki, oraz odbior lewej strony z procesu rank_prev 
      MPI_Sendrecv(sendv_velocity_angles_next.data(), data_size, MPI_DOUBLE, rank_next, 1000,
      recv_velocity_angles_left.data(), data_size, MPI_DOUBLE, rank_prev, 1000, 
      MPI_COMM_WORLD, MPI_STATUSES_IGNORE);


      // na odwrot wysylanie swojej lewej scianki i odbior jako prawa z procesu rank_next 
      MPI_Sendrecv(sendv_velocity_angles_prev.data(), data_size, MPI_DOUBLE, rank_prev, 2000, recv_velocity_angles_right.data(), data_size, MPI_DOUBLE, rank_next, 2000, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
      
      // odpakowanie do wysylko
      idx = 0;
      for(int c = this->cols_from; c <= this->cols_to; ++c)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          this->net->set_angular_velocity(c, r, this->layers_from-1, recv_velocity_angles_left[idx]);
          this->net->set_angular_velocity(c, r, this->layers_to+1, recv_velocity_angles_right[idx]);
          ++idx;
        }
      
      for(int c = this->cols_from; c <= this->cols_to; ++c)
        for(int r = this->rows_from; r <= this->rows_to; ++r){
          this->net->set_angle(c, r, this->layers_from-1, recv_velocity_angles_left[idx]);
          this->net->set_angle(c, r, this->layers_to+1, recv_velocity_angles_right[idx]);
          ++idx;
        }

      break;
    }
  }
  
}