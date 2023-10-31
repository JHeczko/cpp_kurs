#include "class.h"
#include <iostream>
#include <cstdlib>

using namespace std;
//konsturktor
TArr::TArr(int* buf, std::size_t len){
    this->ptr = new InnerArray;
    ptr->buf = buf;
    ptr->len = len;
    ++ptr->ref;
    #ifdef DEBUG
        cout << "c-tor";
    #endif
}
//konstuktor kopiujacy
TArr::TArr(const TArr& obiekt){
    this->ptr = obiekt.ptr;
    obiekt.ptr->ref++;
    #ifdef DEBUG
        cout << "cc-tor";
    #endif
}
//konstruktor przenaszacy
TArr::TArr(TArr&& obiekt){
    this->ptr = obiekt.ptr;
    obiekt.ptr = nullptr;
    delete obiekt.ptr;
    #ifdef DEBUG
        cout << "c-move";
    #endif
}
//destruktor
TArr::~TArr(){
    this->ptr->buf = nullptr;
    this->ptr->len = 0;
    this->ptr->ref = 0;
    this->ptr = nullptr;
    #ifdef DEBUG
        cout << "Destruktor";
    #endif //zakladam ze nie bede uzywal juz danych w tym strutcie pod koniec programu dlatego je wszystkie niszcze i zmieniam
}
//operator = kopiujacy
const TArr& TArr::operator=(const TArr& obiekt){
    if(this == &obiekt){
        return *this;
    }
    this->ptr = obiekt.ptr;
    obiekt.ptr->ref++;
    #ifdef DEBUG
        cout << "=-cp";
    #endif
    return *this;
}
//operator = przenoszacy
const TArr& TArr::operator=(TArr&& obiekt){
        if(this == &obiekt){
        return *this;
    }
    this->ptr = obiekt.ptr;
    obiekt.ptr = nullptr;
    delete obiekt.ptr;
    #ifdef DEBUG
        cout << "=-move";
    #endif
    return *this;
};