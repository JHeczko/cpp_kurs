#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using size_type = unsigned int;
//using words = std::vector<string>;

void f_spacja(string*, std::vector<string>&, size_type);

void space(std::vector<string>, string * ,int , int);

int main(){
    int n;
    cout << "Jak duza kolumna: ";
    cin >> n;
    ifstream filein;
    std::vector<string> tekst; //std::vector<int> tablica wektorowa zbierajaca poszczegolne slowa z zdania
    string bufor; //bufor w czasie dzialanie petli
    
    filein.open("in.txt");
    int max = 0;
    while(! filein.eof()){
        getline(filein ,bufor, ' ');
        //cout << bufor << "\n";
        remove(begin(bufor), end(bufor), '\n');
        tekst.push_back(bufor);
        if(bufor.length() >= max){
            max = bufor.length();
        }
        bufor.clear();
    }
    if(n <= max){
    n = max;
    }

    filein.clear();
    filein.close();
    tekst.shrink_to_fit();
    cout << "Mamy dokladnie: " << tekst.size() << endl;

    string wydruk;
    vector<string>::iterator it;
    vector<string> bufor2;
    it = tekst.begin();
    int i=0;
    int help=0;
    for(i = 0; i < tekst.size();++i){
        //cout << i << ")przedHelp: " << help << "Co wlatuje to buforu " << tekst[i] << endl; 
        help += tekst[i].length() + 1;
        if(tekst[i].length() == max){
            if(bufor2.size() > 0){
                space(bufor2, &wydruk,  help - tekst[i].length(), n);}
            else{
                cout << "bufor zero";}
            cout << wydruk << endl; 
            cout << tekst[i] << endl;
            bufor2.clear();
            wydruk.clear();
            help = 0;
        }
        else if(help >= n){
            if(bufor2.size() > 0){
                space(bufor2, &wydruk, help - tekst[i].length(), n);}
            else{cout << "bufor zero";}
            cout << wydruk << endl;
            help = tekst[i].length() + 1;
            bufor2.clear();
            wydruk.clear();
            bufor2.push_back(tekst[i]);
        }
        else if(help < n) {
            bufor2.push_back(tekst[i]);
        }
    }
}

void space(std::vector<string> bufor, string* wydruk,int help, int max){
    int countChar = help - bufor.size();
    double spaces = max - countChar;
    int spaceBeetwen = floor(spaces / (bufor.size() - 1));
    int restSpaceBeetwen = spaces - (spaceBeetwen * (bufor.size() - 1));
   // cout << "Funcja: " << "bufor size: "<< bufor.size() << " Znaki: " << help << ' ' << "Znaki bez spacji: " << countChar << "Same spacje do dadanie " << spaces << " Ilosc spacji na jedno miejsce: " << spaceBeetwen << "Pozostale spacje do dodania: " << restSpaceBeetwen;
    *wydruk += bufor[0];
    if(bufor.size() == 1){
        for (int k = 0; k < spaces; k++)
        {
            *wydruk += ' ';
        }
        
    }
    else{
        for(int i = 1; i < bufor.size(); i++){
            for(int j = 0; j < spaceBeetwen; j++){
                *wydruk += ' ';
                if(restSpaceBeetwen != 0){
                    for(int l = 0; l < floor(restSpaceBeetwen / (bufor.size()-1)); ++l){
                    *wydruk += ' ';
                    restSpaceBeetwen--;
                }
                    }
            }
            *wydruk += bufor[i];
        }
    }

}