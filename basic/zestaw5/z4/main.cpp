#include <iostream>
#include <string>

using namespace std;

class DP1{
    public:
        virtual void draw_Rectangle(){
            cout << "Drawing Rectangle from DP1\n";
        };
        virtual void draw_Circle(){
            cout << "Drawing Circle from DP1\n";
        };
    private:
};

class DP2{
    public:
        virtual void draw_Rectangle(){
            cout << "Drawing Rectangle from DP2\n";
        };
        virtual void draw_Circle(){
            cout << "Drawing Circle from DP2\n";
        };
    private:
};

class Drawing{
    public:
        virtual void drawCircle() = 0;
        virtual void drawRectangle() = 0;
        virtual ~Drawing(){};
};

class V1Drawing : public Drawing{
    public:
        V1Drawing(DP1& ref) : ref1(ref){}; 
        virtual void drawCircle() override final{
            ref1.draw_Circle();
        };
        virtual void drawRectangle() override final{
            ref1.draw_Rectangle();
        };
    private:
        DP1& ref1;
};

class V2Drawing : public Drawing{
    public:
        V2Drawing(DP2& ref) : ref2(ref){}; 
        virtual void drawCircle() override final{
            ref2.draw_Circle();
        };

        virtual void drawRectangle() override final{
            ref2.draw_Rectangle();
        };

    private:
        DP2 &ref2;
};

class Shape{
    public:
        Shape(Drawing* p1) : drawLib(p1){};
        virtual void draw() = 0;
        virtual void setLib(Drawing* ptr){
            drawLib = ptr;
        };
        virtual ~Shape(){};
    protected:
        Drawing* drawLib;
};

class Rectangle : public Shape{
    public:
        Rectangle(Drawing* lib) : Shape(lib){};
        void draw(){
            drawLib->drawRectangle();
        }
        ~Rectangle(){};
    private:

};

class Circle : public Shape{
    public:
        Circle(Drawing* lib) : Shape(lib){};
        void draw(){
            drawLib->drawCircle();
        }
        ~Circle(){};
    private:

};

int main() {
    DP1 library1; // pierwsza biblioteka
    DP2 library2; // druga biblioteka 
    
    Drawing *d1 = new V1Drawing( library1 );
    Drawing *d2 = new V2Drawing( library2 );

    Shape *p1 = new Rectangle( d1 );
    Shape *p2 = new Circle( d2 );

    p1->draw(); // rectangle linia V1 
    p2->draw(); // circle okrag V2 
    p1->setLib( d2 );
    p2->setLib( d1 );
    p1->draw(); // rectangle linia V2
    p2->draw(); // circle okrag V1

    delete p1;
    delete p2;
    delete d1;
    delete d2;
}