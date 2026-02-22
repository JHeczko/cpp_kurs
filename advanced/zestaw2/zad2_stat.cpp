#include <iostream>

using namespace std;

// statyczny polimorfizm
template<typename S> void metoda2(S cos) {
	cos->metoda1();
};

class Poli1{
public:
	void metoda1(){
		cout << "Robie cos" << endl;
	}
};

class Poli2{
public:
	void metoda1(){
		cout << "Robie cos innego" << endl;
	}
};

int main(void) {
  Poli1 poli1;
  Poli2 poli2;

  metoda2(&poli1);
  metoda2(&poli2);
}