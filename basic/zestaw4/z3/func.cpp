#include "class.h"
#include <iostream>

using namespace std;

void TArr::getInfo(){
        cout << endl;
        cout << "Dlugosc: " << this->ptr->len << endl;
        if(this->ptr->buf == nullptr){
            cout << "Co w buf: NULLPTR"<< endl;
        }
        else{
            cout << "Co w buf: " << *(this->ptr->buf) << endl;
        }
        cout << "Ilosc referencji: " << this->ptr->ref << endl << endl;
}


void TArr::zmienCos(int* buf , std::size_t len){
    --this->ptr->ref;
    this->ptr = new InnerArray;
    this->ptr->buf = buf;
    this->ptr->len = len;
    this->ptr->ref = 1;

}