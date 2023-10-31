#include <string>
#include "z1class.h"
#include <iostream>

using namespace std;

NewClass::NewClass(std::string string){
    this->string = string;
    #ifdef DEBUG
        cout << "Wywoalnie cosntructora: " << this->string << endl;
    #endif
}
NewClass::~NewClass(){
    #ifdef DEBUG
        cout << "Wywoalnie destructora" << endl;
    #endif
}
NewClass::NewClass(const NewClass& obiekt){
    this->string = obiekt.string;
    #ifdef DEBUG
        cout << "Wywoalnie cc-tora: "<< obiekt.string << endl;
    #endif
};
NewClass::NewClass(NewClass&& obiekt){
    if(this != &obiekt){
        this->string = obiekt.string;
        obiekt.string.erase(obiekt.string.begin(), obiekt.string.end());
    }
    #ifdef DEBUG
        cout << "Wywoalnie operatora mvc-tora: "<< this->string << endl;
    #endif 
}
NewClass& NewClass::operator= (const NewClass& obiekt){
    if(this != &obiekt){  
        this->string = "";
        this->string = obiekt.string;
    }
    #ifdef DEBUG
        cout << "Wywoalnie operatora= przenoszacego: "<< obiekt.string << endl;
    #endif
    return *this;
}
NewClass& NewClass::operator= (NewClass&& obiekt){
    if(this != &obiekt){  
        this->string = "";
        this->string = obiekt.string;
        obiekt.string.erase(obiekt.string.begin(), obiekt.string.end());
    }
    #ifdef DEBUG
        cout << "Wywoalnie operatora= poruszajacego: "<< this->string << endl;
    #endif
    return *this;
} 

