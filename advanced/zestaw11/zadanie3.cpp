#include <vector>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
requires std::copyable<T>
class MyVector{
private:
  unique_ptr<vector<T>> v;

public:
  MyVector() : v(std::make_unique<vector<T>>()) {}

  // Konstruktor kopiujący
  MyVector(const MyVector& other) : v(make_unique<vector<T>>(*other.v)) {}

  // Operator przypisania kopiujący
  MyVector& operator=(const MyVector& rhs) {
    if (this != &rhs) {
      *v = *(rhs.v);  // kopiujemy zawartość vector
    }
    return *this;
  }

  void push_back(T item) {
    v->push_back(item);
  }

  void print_all() {
    for (const auto& el : *v) {
      cout << el << " ";
    }
    cout << endl;
  }
};

// dla testu klasa
class NonCopyable {
public:
  //s
  // NonCopyable& operator=(const NonCopyable&) = delete;
};

int main() {
  MyVector<int> v1;           // ✅ OK, int jest kopiowalny
  v1.push_back(42);

  MyVector<NonCopyable> v2;   // ❌ Błąd kompilacji! Typ nie spełnia std::copyable
}