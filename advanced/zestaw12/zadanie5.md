# Visitor
**Opis i funkcja wzorca:**
Jest to behawioralny wzorzec projektowy, który oddziela operacje na obiektach od samych obiektów. Algorytmy dzialaja w sepracji od obiektow na ktorcyh pracuja


**Zastosowanie i problemy, które rozwiązuje:**

* Umożliwia dodawanie nowych operacji bez modyfikowania klas, na których operują
* Przestrzega zasady otwarte-zamknięte (Open/Closed Principle)
* Pomaga oddzielić logikę przetwarzania od struktury danych

**Typowe przypadki użycia:**

* Operacje na strukturach składniowych (np. AST)
* Generowanie raportów, eksport danych
* Walidacja lub analiza danych

**Implementacja w C++:**

```c++
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

```

**Zalety:**

* Zachowanie zasady otwarte/zamkniete, bo pozwala dodawac funckjonalnoc do obiektow roznych klas bez zmiany tych klas(jest metoda accept, ale on jest trywialna)
* Zasada pojedynczej odpowiedzalnosc, wiele roznych wersji jednego zachowania w jednej klasie(generator xml na przyklad)
* Pomaga zebrac informacje o roznych obiektach

**Wady:**

* Trzeba aktualizowac odwiedzajacych, za kazdym razem jak dodamy nowa klase, z ktorej odwiedzajacy ma korzystac
* czasami brak dostepu do prywatncyh skladowych klasy przez odwiedzajacyh

> [!NOTE] Zasada otwarte/zamkniete
> Oznacza mniej wiecej tyle, ze obiekty klas powinny byc otwarte na rozszerzenia, a zamkniete na modyfikacje. Innymi słowy: powinniśmy móc dodać nowe zachowania bez zmieniania istniejącego kodu. Anty przykładem może być coś takiego:
> ```c++
> class Shape {
> public:
>     virtual string getType() = 0;
> };
> 
> class Circle : public Shape {
> public:
>     string getType() override { return "circle"; }
> };
> 
> class Rectangle : public Shape {
> public:
>     string getType() override { return "rectangle"; }
> };
> 
> class AreaCalculator {
> public:
>     double calculate(Shape* shape) {
>         if (shape->getType() == "circle") {
>             // oblicz pole koła
>         } else if (shape->getType() == "rectangle") {
>             // oblicz pole prostokąta
>         }
>         // musimy modyfikować za każdym razem, gdy dodamy nowy typ figury
>     }
> };
> ```
> Zamiast tego dobrym rozwiazaniem, ktore zachowuje te zasade jest
> ```c++
>> class Shape {
> public:
>     virtual double area() = 0;
>     virtual ~Shape() = default;
> };
> 
> class Circle : public Shape {
> private:
>     double radius;
> public:
>     Circle(double r) : radius(r) {}
>     double area() override { return 3.14 * radius * radius; }
> };
> 
> class Rectangle : public Shape {
> private:
>     double width, height;
> public:
>     Rectangle(double w, double h) : width(w), height(h) {}
>     double area() override { return width * height; }
> };
> 
> class AreaCalculator {
> public:
>     double calculate(Shape* shape) {
>         return shape->area();
>     }
> };
> ```