#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "class.h"

using namespace std;

int main(int argc, char* argv[]){
    BigInt Liczba1(argv[1]);
    BigInt Liczba2(argv[2]);
    
    Liczba1.print();
    Liczba1.subtract(Liczba2);
    Liczba1.print();
    Liczba1.add(Liczba2);
    Liczba1.print();
}   