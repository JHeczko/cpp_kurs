/*Fibo(n)
Begin
  if n <= 1 then
       Return n;
  else
       Return Call Fibo(n-1) + Call Fibo(n-2);
  endif
End*/


#include <iostream>
#include <iomanip>
#include <cctype>
#include <map>

using namespace std;

long int fibo(long int);
long int fibo2(long int);
std::map<long int,long int> cache;

int main(){
    int w; 
    while(true){
    long int n;
    cout << "Podaj n'ty wyraz ciagu: \n";
    cin >> n;
    cout << "Dla -1 wyjscie, dla 1 kontynuacja: \n";
    cin >> w; 
    switch (w)
    {
        case -1:
            exit(0);
        case 1:
            for(int i = 0; i<=n; i++){
                cout << fibo(i) << endl;
            };
            break;
        default:
            cout << "Zły numer" << "\n";
    }
    }
}

long int fibo(long int n){
    if (n <= 1){
        return n;
    }
    if(cache.find(n) != cache.end()){
        cout << "Znaleziono"; //Znaleziono wypisywane jest podwojnie jezeli pierwszy raz wpisujemy w tablice te liczbe z ciagu, za dru
        return cache[n]; //Za drugim razzem jest wypisywana tylko raz kiedy juz w tej mapie sie znajduje
    };
    long int x = fibo(n-1) + fibo(n-2);
    cache[n] = x;
    return x;
}
