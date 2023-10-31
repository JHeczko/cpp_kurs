#include <iostream>
#include <iomanip>
#include <format>
#include <string>
#include <string_view>

using namespace std;


int main() {
    cout << "setfill i setw:" << endl;
    for(int i = 0; i < 11; i++){
        if(i == 0 || i == 1 || i == 9 || i == 10){cout << std::setfill('*') << setw(11) << "\n";}
        else{cout << "**" << std::setfill(' ') << setw(8) << "**" << "\n";} 
    }
    cout << endl;
    
    string a(2, '*');
    string b(8, ' ');
    string c(10, '*');
    for(int i = 0; i<11; ++i){
        if(i == 0 || i == 1 || i == 9 || i == 10){
            cout << format("{}{}{}\n", a, b, a);}
        else{
            cout << format("{}\n",c);}
    }


}