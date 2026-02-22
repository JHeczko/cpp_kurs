#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

// każdy element jest przetwarzany niezależnie – idealne do rozdziału na rdzenie.
void example_for_each() {
	std::vector<int> data(10'000'000, 2);

	std::for_each(std::execution::par, data.begin(), data.end(), [](int& x) {
			x *= 2;
	});
}

// każdy element in może być niezależnie przetworzony do out.
void example_transform() {
	std::vector<int> in(10'000'000, 10);
	std::vector<int> out(10'000'000);

	std::transform(std::execution::par, in.begin(), in.end(), out.begin(), [](int x) {
			return x * x;
	});
}

//  dane są tylko odczytywane, więc łatwo dzielone między rdzenie.
void example_count_if() {
	std::vector<int> data(10'000'000);
	std::iota(data.begin(), data.end(), 0);

	auto count = std::count_if(std::execution::par, data.begin(), data.end(),
														 [](int x) { return x % 2 == 0; });

	std::cout << "Parzystych: " << count << "\n";
}

// operacja sumowania (+) jest łączna i przemienna – można ją rozbić między rdzenie.
void example_reduce() {
	std::vector<int> data(10'000'000, 1);
	int sum = std::reduce(std::execution::par, data.begin(), data.end(), 0);
	std::cout << "Suma: " << sum << "\n";
}

// algorytmy sortowania (np. introsort) potrafią dzielić dane między wątki i sortować je lokalnie, a potem scalać.
void example_sort() {
	std::vector<int> data(10'000'000);
	std::generate(data.begin(), data.end(), rand); // losowe dane

	std::sort(std::execution::par, data.begin(), data.end());
}

int main() {
  example_for_each();
  example_transform();
  example_count_if();
  example_reduce();
  example_sort();
}