#include <iostream>

using std::cout;
using std::endl;

template<int K,int  N,bool isEven> struct FastPowCalc; // Ogolna deklaracja

template<int K,int  N> struct FastPowCalc<K, N, true> { // Pierwszy przypadek - parzyste
	enum {
		val = FastPowCalc<K * K, N / 2, (N / 2) % 2 == 0>::val
	};
};

template<int K,int  N> struct FastPowCalc<K, N, false> { // Drugi przypadek - nieparzyste
	enum {
		val = K * FastPowCalc<K, N - 1, (N - 1) % 2 == 0>::val
	};
};

template<int K> struct FastPowCalc<K,0,false> {
	enum {
		val = 1
	};
};

template<int K> struct FastPowCalc<K,0,true> {
	enum {
		val = 1
	};
};

template<int K,int  N> struct FastPow // Ogolna deklaracja
{
	enum{
		val = FastPowCalc<K, N, N % 2 == 0>::val
	};
};

int main()
{
	cout<< FastPow<3,4>::val <<endl;
	cout<< FastPow<2,7>::val <<endl;
	return 0;
}