#include <iostream>
#include <vector>

using namespace std;

class Dot;
class Square;
class Circle;

class Visitator {
public:
  virtual void visit_dot(Dot* d) = 0;
  virtual void visit_square(Square* s) = 0;
  virtual void visit_circle(Circle* c) = 0;
};

class Shape {
public:
  virtual void accept(Visitator* v) = 0;
  virtual ~Shape() {}
};

class Dot : public Shape {
public:
  void accept(Visitator* v) override {
    v->visit_dot(this);
  }
};

class Square : public Shape {
public:
  void accept(Visitator* v) override {
    v->visit_square(this);
  }
};

class Circle : public Shape {
public:
  void accept(Visitator* v) override {
    v->visit_circle(this);
  }
};

class XMLVisitor : public Visitator {
public:
  void visit_dot(Dot* d) override {
    cout << "Turbo specyficzna metoda generowania XML dla dot" << endl;
  }

  void visit_square(Square* s) override {
    cout << "Turbo specyficzna metoda generowania XML dla square" << endl;
  }

  void visit_circle(Circle* c) override {
    cout << "Turbo specyficzna metoda generowania XML dla circle" << endl;
  }
};

int main() {
  vector<Shape*> shapes = {
    new Dot(), new Square(), new Circle(),
    new Dot(), new Square(), new Circle()
};

  XMLVisitor visitor;

  for (Shape* s : shapes) {
    s->accept(&visitor);
  }

  for (Shape* s : shapes) {
    delete s;
  }

  return 0;
}
