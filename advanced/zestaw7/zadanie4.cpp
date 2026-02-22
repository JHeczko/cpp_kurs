#include <iostream>
#include <cmath>
#include "powx.h"
#include "factorial.h"

template<int N> double sin(double x) {
	return sin<N-1>(x) + (N%2?1:-1)*pow<(2*N-1)>(x)/factorial<2*N-1>::val;
}

template<> double sin<0>(double x) {
	return 0;
}

template<int N> double inner(double *a, double *b) {
	return (*a)*(*b)+inner<N-1>(++a,++b);
}

template<> double inner<1>(double *a, double *b) {
	return (*a)*(*b);
}

int main()
{
	std::cout << "Wlasna: " << sin<10>(1) << ", std: "<< sin(1) << std::endl;
	std::cout << "Wlasna: " << sin<10>(3) << ", std: "<< sin(3) << std::endl;
	std::cout << "Wlasna: " << sin<10>(4) << ", std: "<< sin(4) << std::endl;
	std::cout << "Wlasna: " << sin<10>(5) << ", std: "<< sin(5) << std::endl;
	std::cout << "Wlasna: " << sin<10>(6) << ", std: "<< sin(6) << std::endl;


	std::cout << "Wlasna: " << sin<10>(7) << ", std: "<< sin(7) << std::endl;
	std::cout << "Wlasna: " << sin<10>(8) << ", std: "<< sin(8) << std::endl;
	std::cout << "Wlasna: " << sin<10>(10) << ", std: "<< sin(10) << std::endl;


	// std::cout << "Wlasna: " << sin<10>(45) << ", std: "<< sin(45) << std::endl;
	// std::cout << "Wlasna: " << sin<10>(90) << ", std: "<< sin(90) << std::endl;
	return 0;
}