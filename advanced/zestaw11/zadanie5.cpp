#include <iostream>
#include <concepts>
#include <string>

using namespace std;

template<class T>
void describe(T t){
  cout << "Ogolny przypadek: " << t << endl;
};

template<std::integral T>
void describe(T t){
  cout << "Tylko integrale: " << t << endl;
};

int main(){
  describe(3);
  describe(3.14);
  describe("hello");
}