#include <iostream>
#include <string>
#include "class.h"
#include <ostream>


using namespace std;

class liczba;

ostream& operator<<(ostream& stream, liczba obiekt);

class liczba{
    private:
        int i{0};
    public:
        friend ostream& operator<<(ostream& stream, liczba obiekt);
        liczba(int x = 0): i(x){};
        int test(){return 28;};
};

ostream& operator<<(ostream& stream, liczba obiekt){
    return (stream << obiekt.i); 
}


int main(){
    //przyklad dzialania na jakies klasie, liczbe i znaku; 
    liczba i(20);
    SmartPtr<liczba> ptr(new liczba);
    *ptr = i;
    cout << *ptr << endl;
    cout << ptr->test() << endl;

    int x = 25;
    SmartPtr<int> ptr2(new int);
    *ptr2 = x;
    cout << *ptr2 << endl;

    char a = 'C';
    SmartPtr<char> ptr3(new char);
    *ptr3 = a;
    cout << *ptr3 << endl;


}