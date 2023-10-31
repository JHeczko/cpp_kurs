#include <iostream>
#include <string>

class Liczba{
    public:
        //konstruktory
        Liczba(int x = 0) : i(x){};
        //operatory
        Liczba& operator+(const Liczba&);
        Liczba& operator-(const Liczba&);
        Liczba& operator--();
        Liczba& operator--(int);
        Liczba& operator++();
        Liczba& operator++(int);
        //methods
        void getInfo() const{
            std::cout << "Liczba: " << i << std::endl;
        };
    private:
        int i{0};

};