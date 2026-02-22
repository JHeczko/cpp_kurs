```txt
7. Opisz sposób wykorzystania szablonów wyrażeń wektorowych (na podstawie przygotowanego wcześniej kodu)
	 do efektywnego obliczenia wyrażeń wektorowych np.:

	 Vector v1(100, 1);
	 Vector v2(100, 2);
	 Vector res(100);

	 res = 1.2 * v1 + v1 * v2 + v2 * 0.5;
*/
```

Nie bedziemy wtedy generowali 5 tymczasowych kopii obiektu std wektor. Zoptymalizujemy to lepiej. Przykładowo, jesli mamy funkcje
```c++
template<typename T> vector<T> operator+(const vector<T> &lhs,
                                         const vector<T> &rhs) {
vector<T> res(lhs) ;
  for(size_t i=0;i<rhs.size();++i) 
    res[i]+=rhs[i];
  return res;
};

vector<double> v1(100,1);
vector<double> v2(100,2);
vector<double> res(100);
res=1.2*v1+v1*v2+v2*0.5;
```

To jej wywołanie poskutkuje takim analogicznym kodem:
```c++
vector<double> tmp1(100);
tmp1=0.5*v2;
vector<double> tmp2(100);
tmp2=v1*v2;
vector<double> tmp3(100);
tmp3=tmp1+tmp2
vector<double> tmp4(100);
tmp4=1.2*v1;
vector<double> tmp5(100);
tmp5=tmp3+tmp4;
res=tmp5
```


Zaczynamy więc od zdefiniowania nowej klasy Vector. Nie możemy użyć std::vector bezpośrednio, bo potrzebujemy przeładować operator przypisania, ale możemy wykorzystać std::vector do implementacji naszej klasy,

```c++
class Vector : public vector<double> {

public:
  Vector():vector<double>(){};
  Vector(int n):vector<double>(n){};
  Vector(int n,double x):vector<double>(n,x){};
  Vector(const Vector& v):vector<double>(static_cast<vector<double> >(v)){};
  Vector(const vector<double>& v):vector<double>(v) {};
  Vector &operator=(const Vector& rhs) {
     vector<double>::operator=(static_cast<vector<double> >(rhs));
  }

template<typename V>  Vector &operator=(const V &rhs) {
  for(size_t i =0 ;i<vector<double>::size();++i) 
    (*this)[i]=rhs[i];
  return *this;
}
};
```

Dziedziczymy cały interfejs z std::vector ale musimy zdefiniować własne konstruktory. Definiujemy też nowy operator przypisania. Korzystając z szablonów możemy uczynić argumentem operatora przypisania jakiekolwiek wyrażenie, które posiada operator indeksowania:

```c++
class Const_vector {
  double _c;
public:
  Const_vector(double c):_c(c) {};
  double operator[](int i) const {return _c;}
};
```

(Patrzac na stare operatory, ktore robilismy wczesniej )W takim przypadku operator+(...) tworzy tymczasowy obiekt typu Const_vector, który przekazuje do konstruktora AddVectors<LHS,Const_vector>. Taki obiekt nie może być przechowywany przez referencję, bo przestaje istnieć poza zakresem operatora dodawania. Obiekty tego typu muszą wiec być przechowywane jako kopie. Można to łatwo zaimplementować za pomocą klasy cech:

```c++
template<typename T> struct V_expr_traits {
  typedef  T const & op_type;
}  ;
template<> struct V_expr_traits<Const_vector> {
  typedef  Const_vector  op_type;
}  ;
```

za pomocą której definiujemy pola składowe AddVectors jako:
```c++
typename V_expr_traits<LHS>::op_type _lhs;
typename V_expr_traits<RHS>::op_type _rhs
```