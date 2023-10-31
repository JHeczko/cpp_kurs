#include <iostream>
#include "klasa.h"
#include <compare>
#include <tuple>

using namespace std;

int main(){
    TKlasa obj("Cos tama");
    TKlasa obj2("Cos tam");
    TKlasa obj3("jescze inne");

    const char* adres = obj["ma"];
    
    if(adres == nullptr){
        cout << "Nullptr";
    }
    else{
        cout << &adres;
        }

    auto wynik = (obj <=> obj2);

    if(wynik == 0){
        cout << "Rowne";
    }
    else if(wynik < 0){
        cout << "Mniejsze";
    }
    else if(wynik > 0){
        cout << "Wieksze";
    }
}

