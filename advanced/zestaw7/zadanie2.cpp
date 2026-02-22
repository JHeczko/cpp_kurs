#include<iostream>
using namespace std;

// ZAD 1
template<int  N> struct Pow3 {
	enum {
		val = 3 * Pow3<N-1>::val
		};
};

template<> struct Pow3<0> {
	enum {
		val = 1
	};
};

// ZAD 2
template<int K,int  N> struct Pow {
	enum {
		val = K * Pow<K,N-1>::val
	};
};

template<int K> struct Pow<K,0> {
	enum {
		val=1
	};
};


int main()
{
	// ZAD 1
	cout<< Pow3<4>::val <<endl;

	// ZAD 2
	cout<< Pow<3,4>::val <<endl;
	cout<< Pow<2,8>::val <<endl;
	return 0;
}