#include "class.h"
#include <iostream>

using namespace std;

Liczba& Liczba::operator+(const Liczba& obiekt){
    this->i += obiekt.i;
    return *this;
};
Liczba& Liczba::operator-(const Liczba& obiekt){
    this->i -= obiekt.i;
    return *this;
};
Liczba& Liczba::operator--(){
    this->i = this->i - 1;
    return *this;
};
Liczba& Liczba::operator--(int i){
    this->i = this->i - 1;
    return *this;
};
Liczba& Liczba::operator++(){
    this->i = this->i + 1;
    return *this;
};
Liczba& Liczba::operator++(int i){
    this->i = this->i + 1;
    return *this;  
};