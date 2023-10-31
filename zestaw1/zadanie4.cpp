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

using namespace std;

long int fibo(long int n);
long int fibo2(long int n);

int main(){
    int w;
    long int n;
    cout << "Podaj n'ty wyraz ciagu: ";
    cin >> n;  
    while(true){
    cout << "1) Rekurencja 2)For loop: ";
    cin >> w;
    switch (w)
    {
        case 1:
            for(int i = 0; i<=n; i++){
                cout << fibo(i) << endl;
            };
            exit(0);
        case 2:
            for(int i = 0; i<=n; i++){
                cout << fibo2(i) << endl;
            };
            exit(0);
    default:
        cout << "Zły numer" << "\n";
    }
    }
}

long int fibo(long int n){
    if (n <= 1){
        return n;
    }
    else{
        return fibo(n-1) + fibo(n-2);
    }
}

long int fibo2(long int n){
        long int f3;
        int f1 = 0;
        int f2 = 1;
        if(n == 2 || n == 1){return 1;}
        for(int i = 2; i<=n; ++i){
            f3=f1+f2;                     
            f1=f2;
            f2=f3;               
    }
    return f3;
}
