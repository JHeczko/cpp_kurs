#include <iostream>

template<size_t N>
struct Inner{
	static double dot(double *a,double *b) {
		return (*a)*(*b)+Inner<N-1>::dot(++a,++b);
	}
};

template<>
struct Inner<1>{
	static double dot(double *a,double *b) {
		return (*a)*(*b);
	}
};

template<size_t N>
double dot(double *a,double *b) {
	return Inner<N>::dot(a,b);
};

int main()
{
	double a1[] = {1.0, 2.0, 3.0};
	double b1[] = {4.0, 5.0, 6.0};
	std::cout << dot<3>(a1, b1) << std::endl; //32

	double a2[] = {1.0, 2.0, 3.0, 4.0};
	double b2[] = {5.0, 6.0, 7.0, 8.0};
	std::cout << dot<4>(a2, b2) << std::endl; //70

	double a3[] = {1.0};
	double b3[] = {2.0};
	std::cout << dot<1>(a3, b3) << std::endl; //2

	return 0;
}