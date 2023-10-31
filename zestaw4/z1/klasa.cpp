#include <string>
#include <algorithm>
#include <iostream>
#include "klasa.h"

using namespace std;

TKlasa::TKlasa(const char* c){
    str = c;
}

const char* TKlasa::operator[](const char* c){
    int pos = str.find(c);
    if(pos == -1){
        #ifdef DEBUG
            cout << "npos";
        #endif
        return nullptr;
    }
    else{
        #ifdef DEBUG
            cout << "Nie npos";
        #endif
        cout << pos;
        char* buf = str.data();
        return &buf[pos];
    }
} 