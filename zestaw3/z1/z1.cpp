#include "z1class.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main(){
    NewClass a("Cos tam");
    NewClass b = a;
    NewClass c = std::move(b);
    c = a;
    b = std::move(a);

}