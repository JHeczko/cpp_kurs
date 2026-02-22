/*
2. Stwórz odpowiednie funktory Variable oraz Constant, które mogą być używane jako argumenty funkcji integrate:

	 Variable x;
	 integrate(x, 0, 1, 0.001);

	 integrate(Constant(1.0), 0, 1, 0.001);
*/

#include<iostream>
#include<cmath>

using namespace std;

template<typename F> double integrate(F f,double  min,double max,double ds) {
	double integral=.0;
	for(double x=min;x<max;x+=ds) {
		integral+=f(x);
	}
	return integral*ds;
};

class Variable{
  public:
    Variable(){}
    double operator()(double x){return x;}
};

class Constant{
	private:
  	double _a;
	public:
    Constant(double a):_a(a){};
    double operator()(double x){return _a;}
};

int main() {
	Variable x;
	cout << integrate(x, 0, 1, 0.0001) << endl;

	cout << integrate(Constant(1.0), 0, 1, 0.001) << endl;
}