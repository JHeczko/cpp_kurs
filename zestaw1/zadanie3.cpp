#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

int main(){
    string st1;
    std::getline(std::cin, st1);
    for(int i = 0; i<st1.length();++i){
        st1[i] = tolower(st1[i]);
    }
    while(st1.find(' ') != string::npos){
        st1.erase(st1.find(' '), 1); 
    }
    cout << st1 << endl;
    cout << st1.length() << endl;
    for(int i = 0; i < st1.length(); ++i){
        cout << st1[i] << st1[st1.length() - i -1] << endl;
        if(st1[i] != st1[st1.length() - i -1]){
        cout << "NIE palingram";
        return -1;
        }
    }
    cout << "Palingram";
    return 0;
}
