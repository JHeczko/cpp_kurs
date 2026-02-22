/*
* Pokaż, że używanie wskaźnika typu shared_ptr zapewnia
* wywołanie destruktora w przypadku znikania ostatniego z nich
* */

#include <iostream>
#include <memory>

using namespace std;

class A {
  public:

  ~A() {
    cout << "'A' znika" << endl;
  }
};

int main() {
  shared_ptr<A> p = make_shared<A>();
  shared_ptr<A> q = p;

  cout << "Poczatek: " << p.use_count() << endl;

  q = nullptr;

  cout << "Jeszcze nie znika: " << p.use_count() << endl;

  p = nullptr;

  cout << "Powinno juz zniknac, do tego momentu :D";
}