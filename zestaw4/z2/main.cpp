#include <iostream>
#include "klasa.h"

using namespace std;
using namespace wyjscie;

int main(){
    TComplex numer1(1.5, 2);
    TComplex numer2(1.5, 2);
    TComplex numer4(0,0);
    numer2 = numer2 + numer1;

    TComplex numer3;
    cout << "Sprzezenie zespolone: " << numer1.conj() << endl;

    cout << "Wartosc bezwgledna: " <<  numer1.abs() << endl;

    numer3 = numer2(1,6);
    cout << "Operator funckyjny: "<< numer3 << endl;

    numer2 = numer1*numer2;
    cout << "Przemnozenie: "<< numer2 << endl;

    numer3 = numer1/numer3;
    cout << "Podzielenie: " << numer3 << endl;

    numer3 = numer1/numer4;
    cout << "Podzielenie: " << numer3 << endl;
}