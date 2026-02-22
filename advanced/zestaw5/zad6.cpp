/*
 *Napisz funkcje zwracające:
 *długość listy typów, typ dla określonego indeksu listy
 *typów oraz taką, która sprawdza
 *czy dany typ jest wymieniony w podanej liście typów.
 */

#include "zad6.h"

#include <iostream>
#include <type_traits>

template<typename T>
struct Length {
	static const int value = 1 + Length<typename T::Tail>::value;
};

template<>
struct Length<Null_type> {
	static const int value = 0;
};


using MyList = TypeList<int, TypeList<double, TypeList<char, Null_type> > >;

int main() {
	std::cout << "Dlugosc listy: " << Length<MyList>::value << "\n"; // oczekiwane: 3

	using T2 = At<2, MyList>::Result;
	std::cout << "Czy 2-gi typ to double? " << std::boolalpha << std::is_same<T2, double>::value << "\n";

	std::cout << "Czy char jest w liscie? " << In<char, MyList>::yes << "\n";

	std::cout << "Czy float jest w liscie? " << In<float, MyList>::yes << "\n";

	return 0;
}



