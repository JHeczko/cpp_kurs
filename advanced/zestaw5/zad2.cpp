/*
 * 2. Napisz szablon, który sprawdza czy jego parametr posiada
 * typ stowarzyszony value_type,
 * np.: has_value_type<std::vector<int> >::yes
 * powinno mieć wartość true, a has_value_type<int>::yes
 * wartość false.
 * */

#include <iostream>
#include <vector>
#include <map>

template<typename T>
struct has_value_type {
private:
	// Jeśli T::value_type istnieje, ta wersja zostanie wybrana
	template<typename U>
	static char test(typename U::value_type*);

	// Jeśli T::value_type nie istnieje, fallback
	template<typename U>
	static int test(...);

public:
	enum { yes = sizeof(test<T>(nullptr)) == sizeof(char) };
};

int main() {
	std::cout << "std::vector<int> ma value_type? " << has_value_type<std::vector<int>>::yes << "\n";
	std::cout << "int ma value_type? " << has_value_type<int>::yes << "\n";
	std::cout << "std::map<int, double> ma value_type? " << has_value_type<std::map<int, double>>::yes << "\n";

	return 0;
}
