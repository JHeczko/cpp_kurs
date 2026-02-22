#include <iostream>

using std::cout;
using std::endl;

template<size_t N> struct factorial {
	enum {val=N*factorial<N-1>::val};
};

template<> struct factorial <0>{
	enum {val=1};
};

int main()
{
	cout << factorial<5>::val << endl;
	return 0;
}