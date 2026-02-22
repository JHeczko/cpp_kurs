#include <concepts>
#include <iostream>

using namespace std;

void intable(std::integral auto i){
	cout << "Only integral types" << i << endl;
};

template<typename T>
void intable2(T i)
requires std::integral<T>
{
	cout << "Only integral types" << i+i << endl;
};

int main() {
  int i = 2;
  intable(i);
	intable2(i);

	bool j = true;
	intable(j);
	intable2(j);

	// double k = 3.123;
	// intable(k);
	// intable2(k);

	// string cos = "jakiscosiek";
	// intable(cos);
	// intable2(cos);
}