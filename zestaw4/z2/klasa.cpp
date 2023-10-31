#include "klasa.h"
#include "wyjscie.h"
#include <iostream>
#include <math.h>
#include <ostream>

using namespace std;

TComplex TComplex::operator+(const TComplex& obiekt) const{
    TComplex zwrot;
    zwrot.re = this->re + obiekt.re;
    zwrot.im = this->im + obiekt.im;
    return zwrot;
}
TComplex TComplex::operator-(const TComplex& obiekt) const{
    TComplex zwrot;
    zwrot.re = this->re - obiekt.re;
    zwrot.im = this->im - obiekt.im;
    return zwrot;
}
TComplex::TComplex(const TComplex& obiekt){
    this->re = obiekt.re;
    this->im = obiekt.im;
}
TComplex::TComplex(TComplex&& obiekt){
    this->re = obiekt.re;
    this->im = obiekt.im;
    obiekt.re = 0;
    obiekt.im = 0;
}
TComplex& TComplex::operator=(const TComplex& obiekt){
    this->re = obiekt.re;
    this->im = obiekt.im;
    #ifdef DEBUG
        cout << "cc-tor";
    #endif
    return *this;
}
TComplex& TComplex::operator=(TComplex&& obiekt){
    this->re = obiekt.re;
    this->im = obiekt.im;
    obiekt.re = 0;
    obiekt.im = 0;
    #ifdef DEBUG
        cout << "mvc-tor";
    #endif
    return *this;
}
TComplex TComplex::operator()(double im, double re){
    TComplex zwrot(im,re);
    return zwrot;
}
void TComplex::getValue() const{
    std::cout << "CZESC RZECZYWISTA: " << re << "CZESC UROJONA: " << im << std::endl;
}
TComplex TComplex::conj() const{
    TComplex buf((this->re), -(this->im));
    return buf;
}
double TComplex::abs() const{
    double buf = sqrt(pow(this->re, 2) + pow(this->im, 2));
    return buf;
}
TComplex TComplex::operator*(const TComplex& obiekt) const{
    TComplex buf;
    buf.re = ((this->re * obiekt.re) - (this->im * obiekt.im));
    buf.im = ((this->re * obiekt.im) - (this->im * obiekt.re));
    return buf;
}

TComplex TComplex::operator/(const TComplex& obiekt) const{
    TComplex buf;
    if((pow(obiekt.im,2) + (pow(obiekt.re,2))) == 0){
        cout << "Dzielenie przez zero" << endl;
        return TComplex(0,0);
    }
    buf.re = ((this->re * obiekt.re) + (this->im * obiekt.im)) / (pow(obiekt.im,2) + (pow(obiekt.re,2)));
    buf.re = ((this->im * obiekt.re) - (this->re * obiekt.im)) / (pow(obiekt.im,2) + (pow(obiekt.re,2)));
    return buf;
}

ostream& wyjscie::operator<<(ostream& strumien, const TComplex& obiekt){
    strumien <<'(' << obiekt.re << " , " << obiekt.im <<')';
    return strumien;
}