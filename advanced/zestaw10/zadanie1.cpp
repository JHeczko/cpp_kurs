#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

using namespace std;

// std::execution::sequenced_policy
// Opis: Algorytm działa sekwencyjnie, tzn. każdy element jest przetwarzany jeden po drugim w kolejności, bez współbieżności. Gwarantowana deterministyczność – używane tam, gdzie zależność między elementami jest ważna.
int seq() {
	std::vector<int> data = {5, 4, 3, 2, 1};
	std::sort(std::execution::seq, data.begin(), data.end());

	for (int n : data) std::cout << n << " ";
	return 0;
}

// std::execution::parallel_policy
// Opis: Algorytm może wykorzystywać wiele wątków, ale zachowuje kolejność logiczną operacji (bez wektoryzacji). Dobre dla algorytmów intensywnych obliczeniowo, gdzie nie ma zależności między elementami.

int par(){
	std::vector<int> data(1'000'000, 1);

	// Równoległe przetwarzanie: dodaj 5 do każdego elementu
	std::for_each(std::execution::par, data.begin(), data.end(),
								[](int& x) { x += 5; });

	std::cout << "Pierwszy element: " << data[0] << "\n";
	return 0;
}

// std::execution::parallel_unsequenced_policy
// Algorytmy mogą działać równolegle i z wektoryzacją (SIMD), bez gwarancji kolejności. Maksymalna wydajność, ale brak gwarancji kolejności – elementy mogą być przetwarzane losowo.

int parr_vec(){
	std::vector<int> data(1000000, 1);

	// Przetwarzanie równoległe i wektorowe
	std::transform(std::execution::par_unseq, data.begin(), data.end(), data.begin(),
								 [](int x) { return x * 2; });

	std::cout << "Pierwszy element: " << data[0] << "\n";
	return 0;
}

int main(){
  seq();

  par();

  parr_vec();

  return 0;
}

