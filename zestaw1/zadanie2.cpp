#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main(){
    //char a[5];
    char c[6];
    char a[6];
    cout << "Podaj dwa slowa o 5 dlugosci dlugosci: " << "\n";
    scanf("%s", a);
    scanf("%s", c);
    printf("%s %s \n",a, c);
    for (int i = 0; i<5; ++i){
        a[i] = tolower(a[i]);
        c[i] = tolower(c[i]);
    }
    for(int i = 0; i<5; ++i){
        cout << a[i] << c[i] << endl;
        if (a[i] != c[i]){
            cout << "nie zgadza sie";
            return -1;}
    }
    cout << "Wszystko ok";
    return 0;    
}

