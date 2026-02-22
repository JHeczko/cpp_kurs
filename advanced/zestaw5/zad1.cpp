/*
 * 1. Zaimplementuj szablon is_class służący do sprawdzania czy dany typ jest klasą.
 */

#include <iostream>

using namespace std;

template<typename T> class Is_class {

	typedef char one;
	typedef struct {char c[2];} two;

	template<typename U> static one test(int U::*);
	template<typename U> static two test(...);

public:
	enum {yes = (sizeof(test<T>(0))==sizeof(one) )};
};

struct MyStruct {};
enum MyEnum {};
typedef int MyInt;

int main(){
	std::cout << Is_class<MyStruct>::yes << std::endl;
	std::cout << Is_class<MyEnum>::yes << std::endl;
	std::cout << Is_class<MyInt>::yes << std::endl;
}