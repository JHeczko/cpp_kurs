#include <iostream>
#include <concepts>
#include <string>

using namespace std;

template <typename T>
requires std::integral<T>
void describe(T t){
  cout << "Integral: " << t << endl;
};

template <typename T>
requires std::floating_point<T>
void describe(T t){
  cout << "Floating point: " << t << endl;
};

template <typename T>
requires std::same_as<T, std::string>
void describe(T t){
  cout << "String: " << t << endl;
};

int main() {
  describe(42);
  describe(3.14);
  describe(std::string("Elo zelo"));
}