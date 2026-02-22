#include <iostream>
#include <typeinfo>


using namespace std;

// zadanie 1
template<typename T> T maksimum(T a, T b) {
  return a>b ? a : b;
}

// zadanie 2
template<typename C_out, typename C_in> C_out convert(C_in a) {
  return static_cast<C_out>(a);
}

// zadanie 3
template<size_t N, typename T> T dot_product(T* a, T* b) {
  T dot = 0.0;
  for (int i = 0; i < N; ++i) {
    dot += a[i] * b[i];
  }
  return dot;
}

// zadanie 4
template<int N> struct SomeStruct {
  int a = N;
};

template<int K,template<int N> class C> void f(C<K> klasa) {
  cout << K << endl;
}

// zadanie 5
template<typename T,size_t N>
class Stack
{
private:
  T data[N];
  size_t top;
public:
  //typedef T value_type;
  using value_type = T;

  Stack():top(0) {};

  void push(T val)
  {
    data[top++]=val;
  }

  T pop()
  {
    return data[--top];
  }
  bool is_empty() const
  {
    return (top==0);
  }
};

template<typename S> typename S::value_type suma(S s) {
  typename S::value_type total = 0;
  while(!s.is_empty())
  {
    total+=s.pop();
  }
  return total;
}

int main() {
  int a = 3;
  int b = 7;
  // test 1
  cout << ::maksimum<int>(a, b) << endl;

  // test2
  cout << typeid(convert<double>(b)).name() << " | " << typeid(convert<short>(b)).name() << endl;

  // test3
  int c[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int d[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  cout << "Dot product: " << dot_product<9>(c, d) << endl;

  //test4
  SomeStruct<10> s;
  f(s);

  //test5
  Stack<int,3> stos;
  stos.push(1);
  stos.push(2);
  stos.push(4);
  cout << "Zadanie 5: " << endl << suma(stos) << endl;
  return 0;
}