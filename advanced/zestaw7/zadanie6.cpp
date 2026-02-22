#include <iostream>

template<size_t N,typename T> struct Inner {
	static T dot(T *a,T *b) {
		return (*a)*(*b)+Inner<N-1,T>::dot(a+!,b+1);
	}
};

template<typename T > struct Inner<1,T> {
	static T dot(T *a,T *b) {
		return (*a)*(*b);
	}
};

template<size_t N,typename T> T dot( T *a,T *b) {
	return Inner<N,T>::dot(a,b);
};

int main()
{
	double a1[] = {1.0, 2.0, 3.0};
	double b1[] = {4.0, 5.0, 6.0};
	std::cout << dot<3>(a1, b1) << std::endl; //32

	int a2[] = {1, 2, 3, 4};
	int b2[] = {5, 6, 7, 8};
	std::cout << dot<4>(a2, b2) << std::endl; //70

	short a3[] = {1};
	short b3[] = {2};
	std::cout << dot<1>(a3, b3) << std::endl; //2

	return 0;
}