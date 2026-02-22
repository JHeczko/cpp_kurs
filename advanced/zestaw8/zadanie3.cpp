/*
3. Funktor AddExpr jest używany przez szablon operatora dodawania dwóch funktorów:

	 template<typename LHS,typename RHS > AddExpr<LHS,RHS> operator+(const LHS &l, const RHS &r)

	 zwracany funktor może być podstawiony do funkcji całkującej. Dokonaj specjalizacji szablonu operatora dodawania
	 dla przypadku, w którym jeden z argumentów jest typu double, tak aby możliwe było następujące użycie funkcji integrate:

	 integrate(x + 1., 0, 1, 0.001);
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

// ============= Klasa zmiennej =============

class Variable{
public:
	Variable(){}
	double operator()(double x){return x;}
};

// ============= Klasa stalej =============


class Constant{
private:
	double _a;
public:
	Constant(double a):_a(a){};
	double operator()(double x){return _a;}
};


// ============= Klasa do dodawania =============
template<typename LHS,typename RHS >
class AddExpr {
	LHS _lhs;
	RHS _rhs;
public:
	AddExpr(const LHS &l,const RHS &r) :_lhs(l),_rhs(r) {};

	double operator()(double x) {
		return _lhs(x) + _rhs(x);
	}
};

// Operator dodawania dla dwóch funktorów
template<typename LHS, typename RHS>
AddExpr<LHS, RHS> operator+(const LHS &l, const RHS &r) {
	return AddExpr<LHS, RHS>(l, r);
};

// Operator dodawania dla przypadku, gdzie jeden z operandów to double
template<typename LHS>
AddExpr<LHS, Constant> operator+(const LHS &l, double r) {
	return AddExpr<LHS, Constant>(l, Constant(r));
};

// Operator dodawania dla przypadku, gdzie drugi operand to double
template<typename RHS>
AddExpr<Constant, RHS> operator+(double l, const RHS &r) {
	return AddExpr<Constant, RHS>(Constant(l), r);
}

int main() {
	Variable x;
	cout << integrate(x, 0, 1, 0.001) << endl;

	cout << integrate(Constant(1.0), 0, 1, 0.001) << endl;

	cout << integrate(x + 1., 0, 1, 0.001) << endl;
}