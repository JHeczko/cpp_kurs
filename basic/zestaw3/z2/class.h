#pragma once

#include <iostream>
#include <string>

class BigInt{
    public:
        BigInt(char cos[]); // c-tor
        BigInt(const BigInt&); //cc -tor
        BigInt(BigInt&&); // mvc - tor
        BigInt& operator=( const BigInt& ); //opeartor= c
        BigInt& operator=( BigInt&& ); // operator= mv
        ~BigInt(); //d-tor

        void add(const BigInt&);
        void subtract(const BigInt&);
        void print() const;

    private:
        std::string liczba;


};