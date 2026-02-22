/*
6. Zaimplementuj rozszerzenie klasy Variable dla przypadku funktorów dwóch zmiennych, tj. klasy First oraz Second.
	 Podaj przykład całkowania prostej funkcji np. x + y.
*/
#include <iostream>

using namespace std;

class Variable {
public:
	double operator()(double x) const {
		return x;
	}
};

class Constant {
private:
	double value;
public:
	Constant(double val) : value(val) {}

	double operator()(double x) const {
		return value;
	}
	double operator()(double, double) const {
		return value;
	}
};

template<typename LHS, typename RHS>
class AddExpr {
private:
	LHS _lhs;
	RHS _rhs;
public:
	AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {}

	double operator()(double x) const {
		return _lhs(x) + _rhs(x);
	}
	double operator()(double x, double y) const {
		return _lhs(x, y) + _rhs(x, y);
	}
};

template<typename LHS, typename RHS>
AddExpr<LHS, RHS> operator+(const LHS &l, const RHS &r) {
	return AddExpr<LHS, RHS>(l, r);
}

template<typename LHS>
AddExpr<LHS, Constant> operator+(const LHS &l, double r) {
	return AddExpr<LHS, Constant>(l, Constant(r));
}

template<typename RHS>
AddExpr<Constant, RHS> operator+(double l, const RHS &r) {
	return AddExpr<Constant, RHS>(Constant(l), r);
}

//zadanie 6
class First {
public:
	double operator()(double x) const {
		return x;
	}

	double operator()(double x, double) const {
		return x;
	}
};


class Second {
public:
	double operator()(double, double y) const {
		return y;
	}
};
template<typename F>
double integrate(F f, double min1, double max1, double min2, double max2, double ds) {
	double integral = 0.0;
	for (double x = min1; x < max1; x += ds) {
		for (double y = min2; y < max2; y += ds) {
			integral += f(x, y);
		}
	}
	return integral * ds * ds;
}


int main(){
	auto f = First() + Second();
	std::cout << integrate(f, 0, 1, 0, 1, 0.01) << std::endl;
	return 0;
}