/*
5. Operatory arytmetyczne nie będą miały jak automatycznie wydedukować typu T:

	 template<typename T, typename LHS, typename RHS > Add<T,LHS,RHS> operator+(const LHS &l, const RHS &r)

	 ponieważ typ T nie pojawia się w argumentach wywołania. Zaimplementuj dodatkową klasę Expr "opakowującą" wyrażenia,
	 która będzie przenosiła informację o typie. Przedstaw przykłady całkowania funkcji z użyciem zmiennej innego typu niż double.
*/

#include <iostream>
#include <cmath>
#include <complex>

using namespace std;


template<typename F> double integrate(F f,double  min,double max,double ds) {
	double integral=.0;
	for(double x=min;x<max;x+=ds) {
		integral+=f(x);
	}
	return integral*ds;
};

template<typename T> class Variable {
public:
	T operator()(T x) {
		return x;
	}
};


template<typename T> class Constant {
	T _c;
public:
	Constant(T c) :_c(c){};
	T operator()(T x) {return _c;}
};


template<typename T,typename R = Variable<T> >
class Expr {
	R _rep;
public:
	Expr() {};
	Expr(R rep):_rep(rep) {};
	T operator()(T x) {return _rep(x);}
	R rep() const {return _rep;};
};

// ======= Klasa dodawania =======
template<typename T, typename LHS,typename RHS > class AddExpr {
	LHS _lhs;
	RHS _rhs;
public:
	AddExpr(const LHS &l,const RHS &r) :_lhs(l),_rhs(r) {};
	T operator()(T x) {
		return _lhs(x)+_rhs(x);
	}
};

template<typename T,typename LHS,typename RHS >
Expr<T,AddExpr<T,LHS,RHS> >  operator+(const Expr<T,LHS> &l,
																			 const Expr<T,RHS> &r) {
	return Expr<T,AddExpr<T,LHS,RHS> >(AddExpr<T,LHS,RHS>(l.rep(),r.rep()));
};


template<typename T,typename LHS >
Expr<T,AddExpr<T,LHS,Constant<T> > >
operator+(const Expr<T,LHS>  &l,
					T r) {
	return Expr<T,AddExpr<T,LHS,Constant<T> > >(AddExpr<T,LHS,Constant<T> >(l.rep(),Constant<T>(r)));
};


template<typename T,typename LHS >
Expr<T,AddExpr<T,Constant<T>,LHS > >  operator+(T r,
																								const Expr<T,LHS>  &l) {
	return Expr<T,AddExpr<T,Constant<T>,LHS> >(AddExpr<T,Constant<T>,LHS>(Constant<T>(r),l.rep()));
};

int main() {
	Expr<int> x1;
	std::cout << integrate(x1, 0, 4, 1) << std::endl;
	return 0;
}