#include <iostream>
#include "class.h"
#include <cstdlib>

using namespace std;

int main(){

    int liczba1 = 1234;
    int liczba2 = 12345;

    TArr a(&liczba1, 4);
    TArr b;
    TArr c;

    b = a;
    c = b;
    cout << "Obiekty przzed zmiana" << endl;
    a.getInfo();
    b.getInfo();
    c.getInfo();

    a.zmienCos(&liczba2, 5);
    cout << "obiekt a po zmianie czegos i zrobieniu hard-copy" << endl;
    a.getInfo();
    b.getInfo();
    c.getInfo();

}
