// 2. Sprawdź czy wielkość inteligentnego wskaźnika różni się od wielkości zwykłego wskaźnika

#include <iostream>
#include <memory>

int main() {
	double* a = new double;
	std::unique_ptr<double> b(new double);
	std::shared_ptr<double> c(new double);
	std::cout << "Wielkosc zwyklego wskaznika(raw pointer) = " << sizeof(a) << " b" << std::endl;
	std::cout << "Wielkosc wskaznika unique_ptr  = " << sizeof(b) << " b" << std::endl;
	std::cout << "Wielkosc wskaznika std::shared_ptr = " << sizeof(c) << " b" << std::endl;
	return 0;
}
