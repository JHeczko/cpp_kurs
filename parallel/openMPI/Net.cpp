#include"Net.h"

Net::Net( int cols, int rows, int layers ) {
  angle = new Grid3D( cols, rows, layers );
  angular_velocity = new Grid3D( cols, rows, layers );
}

