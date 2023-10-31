#include "class.h"
#include <iostream>

using namespace std;

int func(int i ){
    return i;
}

int main(){
    Liczba x(2);

    ++++++++++x;

    x.getInfo();

    ----------x;

    x.getInfo();

    x++++++++++;

    x.getInfo();

    x----------;

    x.getInfo();

    x = x + x;

    x.getInfo();

    x = x - x;

    x.getInfo();

    int abc = 123;

    int&& ref = func(abc);

    cout << ref; 


}