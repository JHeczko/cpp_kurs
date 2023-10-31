#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include "wyjscie.h"

class TComplex {
public:
    TComplex(double re = 0.0, double im = 0.0){
        this->re = re;
        this->im = im;
    };
    TComplex(const TComplex&);
    TComplex(TComplex&&);

    TComplex operator+(const TComplex&) const;
    TComplex operator-(const TComplex&) const;
    TComplex& operator=(const TComplex&);
    TComplex& operator=(TComplex&&);
    TComplex operator()(double , double);
    TComplex operator*(const TComplex&) const;
    TComplex operator/(const TComplex&) const;
    friend std::ostream& wyjscie::operator<<(std::ostream&, const TComplex&);

    //(a, b) · (c, d) = (ac − bd, ad + bc)

    void getValue() const;
    double abs() const;
    TComplex conj() const;
private:
    double re, im;
}; 