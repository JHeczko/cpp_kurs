#include <iostream>

using namespace std;

class Square{
  private:
    float side;
  public:
    Square(float side):side(side){}

    float get_side(){
      return side;
    }
};

class Circle{
private:
  float radius;
public:
  Circle(float radius):radius(radius){}

  virtual float get_radius(){
    return radius;
  };

};


class Hole{
  protected:
    float radius;
  public:
    Hole(float radius):radius(radius){};

    bool fits(Circle* c){
      cout << c->get_radius() << endl;
      return true ? c->get_radius()<=radius : false;
    };
};
/*
 * Tutaj pojawia sie problem, bo nie mozemy sprawdzic czy kwadrat zmiesci sie do dziury, jesli podamy
 * tylko dlugosc boku, trzeba sprawdzic, pol przekatnej, wiec robimy klase adapter
* */

class SquareAdapter:public Circle{
private:
  Square* square;
public:
    SquareAdapter(Square* s):square(s),Circle(0){};

    float get_radius() override{
      return square->get_side() * sqrt(2) / 2;
    };
};

int main() {
  Circle* small_circle = new Circle(5);
  Circle* big_circle = new Circle(40);

  Square* small_square = new Square(5);
  Square* big_square = new Square(40);

  SquareAdapter* small_square_Adapter = new SquareAdapter(small_square);
  SquareAdapter* big_square_Adapter = new SquareAdapter(big_square);

  Hole hole(5);

  cout << "Small circle fits: " << hole.fits(small_circle) << endl;
  cout << "Big circle fits: " << hole.fits(big_circle) << endl;
  cout << "Small Adapter fits: " << hole.fits(small_square_Adapter) << endl;
  cout << "Big Adapter fits: " << hole.fits(big_square_Adapter) << endl;
}