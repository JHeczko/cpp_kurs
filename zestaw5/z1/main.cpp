#include <iostream>

using namespace std;

#define P(x) std::cout << x << std::endl

class A1 {
    private:
        int i { 5 };
    public:
        A1(bool a){ P("A1 c-tor"); }; 
        virtual ~A1() { P("A1 d-tor"); }; 
        int get() const { return i; };
};

class V1 : virtual public A1 { 
    public: 
        V1(bool b) : A1(true) { P("V1 c-tor"); }; 
        virtual ~V1() override { P("V1 d-tor"); };
};

class C1 : virtual public V1{
    public:
        C1(bool) : V1(true), A1(true){ P("C1 c-tor"); }; 
        virtual ~C1() override { P("C1 d-tor"); };
};

class B2{
    public:
        B2(bool){ P("B2 c-tor"); }; 
        virtual ~B2() { P("B2 d-tor"); };
};

class B3{
    public:
        B3(bool){ P("B3 c-tor"); }; 
        virtual ~B3() { P("B3 d-tor"); };
};

class V2 : virtual public A1, public B2{
    public:
        V2(bool): A1(true), B2(true){ P("V2 c-tor"); }; 
        virtual ~V2() override { P("V2 d-tor"); };
};

class C2 : virtual public V2, public B3{
    public:
        C2(bool) : V2(true) , B3(true) , A1(true){ P("C2 c-tor"); }; 
        virtual ~C2()override{ P("C2 d-tor"); };
};

class M1{
    public:
        M1(bool = true){ P("M1 c-tor"); }; 
        ~M1() { P("M1 d-tor"); };
};

class M2{
    public:
        M2(bool = true){ P("M2 c-tor"); }; 
        ~M2(){ P("M2 d-tor"); };
};

class X : public C1, public C2 {
    private:
        M1 m1;
        M2 m2;
    public:
        X(bool x = true): C1(true) , C2(true), V2(true) , V1(true) , A1(true){ P("X c-tor"); }; 
        virtual ~X() override final{ P("X d-tor"); };
};

//=========MAIN========

int main() {
    A1 *pa = new X;
    cout << pa->get() << endl; // zakomentować gdy public A1
    delete pa; 
}

/* Podpunkt a)
Dostalem taki blad:

a.out(1150,0x102714580) malloc: *** error for object 0x14d704094: pointer being freed was not allocated
a.out(1150,0x102714580) malloc: *** set a breakpoint in malloc_error_break to debug

Lecz nie bylo to podczas kompilacji ale dzialania programu, to co udalo mi sie wyczytac, to kieyd nie mamy destruktora wirtualnego
i staramy sie zrobic polimorfizm obiektowy przy wskazniku, to bedzie problem poniewaz wskaznik "nie bedzie wiedzial", ze jest jeszcze jakis destruktor do wywolania poza tym z klasy bazowej, czyli tej ktora jest typem wskaznika. Reasumujac, nie wywolaja sie inne konstruktory niz klasy A1, bo nie bedzie w wiadomosci w programie, aby wywolac jeszcze inny niz konstruktor klasy A1

*/

/* Podpunkt b)

Program nawet się nie skompiluje, wyskoczy nam error 

error: ambiguous conversion from derived class 'X' to base class 'A1'

I kilku innych bledow, ktore wywodza sie z tego bledu, w skrocie chodzi o to, ze bez dziedziczenia wirtualnego, mamy problem natury takiej,
ze dziedziczymy tą samą metode int get(), kilka razy w jednym obiekcie, wiec mamy pewna niejasnosc, bo kompilator dostaje, dwie te same metody i niewiadomo, ktora ma wywolac, ten problem mozna byloby zaradzic robiac :: do obiektu, z ktorego potrzebujemy tę metode wyciagnac.
Mozna powiedziec, ze jesli dziedziczymy w lini prostej to slowko "virtual" jest niepotrzebne , a jesli robimy juz takie rozgałęzione dziediczenie, ktore potem zbiega do jednej klasy, to juz potrzebujemy slowko "virtual"  

*/