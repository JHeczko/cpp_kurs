#include <iostream>

using namespace std;

// Dynamiczny polimorfizm
class Base{
public:
	virtual void metoda1() = 0;
};

class Poli1 : public Base{
public:
	void metoda1() override{
		cout << "Robie cos" << endl;
	 }
};

class Poli2 : public Base{
public:
	void metoda1() override{
		cout << "Robie cos innego" << endl;
	}
};

int main(void){
	Poli1* cos1 = new Poli1();
	Poli2* cos2 =  new Poli2();

	Base* lista[] = {cos1,cos2};

	for(int i = 0; i < 2; i++) {
		lista[i]->metoda1();
	}

}