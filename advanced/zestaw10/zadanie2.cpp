#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <mutex>
#include <iostream>
#include <chrono>

int main() {
	std::vector<int> vec(10'000'000);
	std::iota(vec.begin(), vec.end(), 0);

	std::vector<int> output;
	std::mutex mtx;

	auto start = std::chrono::high_resolution_clock::now();

	std::for_each(std::execution::par, vec.begin(), vec.end(),
			[&output, &mtx](int elem) {
					if (elem % 2 == 0) {
							std::lock_guard<std::mutex> lock(mtx);
							output.push_back(elem);
					}
			});

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Czas wykonania (par + mutex): " << duration.count() << " s\n";
	std::cout << "Wynikowy rozmiar: " << output.size() << "\n";

	output.clear();
	auto start2 = std::chrono::high_resolution_clock::now();

	std::for_each(std::execution::seq, vec.begin(), vec.end(),
			[&output](int elem) {
					if (elem % 2 == 0) {
							output.push_back(elem);
					}
			});

	auto end2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration2 = end2 - start2;
	std::cout << "Czas wykonania (seq): " << duration2.count() << " s\n";
}