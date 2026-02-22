#include <string>
#include <iostream>
#include <algorithm>
#include "class.h"

using namespace std;


    BigInt::BigInt(char liczba[]){
        string buf(liczba);
        this->liczba = buf;
        #ifdef debug
            cout << "c-tor: " << this->liczba<< endl;
        #endif
    }

    BigInt::BigInt(const BigInt& obiekt){
        this->liczba = obiekt.liczba;
        #ifdef debug
            cout << "CC-tor" << endl;
        #endif
    }

    BigInt::BigInt(BigInt&& obiekt){
        this->liczba = obiekt.liczba;
        obiekt.liczba.erase();
        #ifdef debug
            cout << "mvc-tor" << endl;
        #endif
    };

    BigInt& BigInt::operator=( const BigInt& obiekt ){
        this->liczba = obiekt.liczba;
        #ifdef debug
            cout << "copy =" << endl;
        #endif
        return *this;
    }

    BigInt& BigInt::operator=( BigInt&& obiekt ){
        this->liczba = obiekt.liczba;
        obiekt.liczba.erase();
        #ifdef debug
            cout << "mv = " << endl;
        #endif
        return *this;
    }

    BigInt::~BigInt(){
        this->liczba.erase();
        #ifdef debug
            cout << "D-tor: " << this->liczba << endl;
        #endif
    }

    void BigInt::add(const BigInt& obiekt){
        long long int a, b, wynik;
        a = stoi(obiekt.liczba);
        b = stoi(this->liczba);
        wynik = a + b;
        this->liczba = std::to_string(wynik);        
    }
    
    void BigInt::subtract(const BigInt& obiekt){
        long long int a, b, wynik;
        a = stoi(obiekt.liczba);
        b = stoi(this->liczba);
        wynik = b - a;
        this->liczba = std::to_string(wynik); 
    }
    
    void BigInt::print() const{
        cout << this->liczba << endl;
    };