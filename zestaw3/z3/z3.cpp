#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <iterator>
#include <stdio.h>

using namespace std;


int main(){

//-----------|DEKLARACJA I DEF ZMIENNYCH|-------------------
    int kolumnaA = 1;
    int wierszeA = 1;
    int kolumnaB = 1;
    int wierszeB = 1;
    std::string buf;
    std::vector<string> buf2;
    fstream filein;


//-------------------|WCZYTYWANIE MACIERZY A|------------------------
    filein.open("mA.txt", ios::in);
    while(getline(filein, buf, ' ')){
        buf2.push_back(buf);
    }
    filein.close();

    for(int i = 0; i < buf2.size() ;++i){
        #ifdef DEBUG
            cout << buf2[i] << " ";
        #endif
        if(buf2[i][0] == '\n'){
            ++wierszeA;
        }
    }
    kolumnaA = floor(buf2.size()/wierszeA);

    int macierzA[wierszeA][kolumnaA];
    int licznik = 0;

    for(int i = 0; i < wierszeA; i++){
        for(int j = 0; j < kolumnaA; j++){
            macierzA[i][j] = stoi(buf2[licznik]);
            licznik++;
        } 
    }
    #ifdef WYPISZ
        for(int i = 0; i < wierszeA; i++){
            for(int j = 0; j < kolumnaA; j++){
                cout << macierzA[i][j] << ' ';
            } 
            cout << endl;
        }
        cout << "-----------------" << endl;
    #endif 

    #ifdef DEBUG
        cout << endl << wierszeA << " " << kolumnaA << endl;
    #endif
    buf2.clear();

//-------------------|KONIEC WCZYTYWANIA MACIERZY A|------------------------

//-------------------|WCZYTYWANIE MACIERZY B|-------------------------------

    filein.open("mB.txt", ios::in);
    while(getline(filein, buf, ' ')){
        buf2.push_back(buf);
    }

    filein.close();

    for(int i = 0; i < buf2.size() ;++i){
        #ifdef DEBUG
            cout << buf2[i] << " ";
        #endif    
        if(buf2[i][0] == '\n'){
            ++wierszeB;
        }
    } 
    kolumnaB = floor(buf2.size()/wierszeB);
    
    int macierzB[wierszeB][kolumnaB];
    licznik = 0;

    for(int i = 0; i < wierszeB; i++){
        for(int j = 0; j < kolumnaB; j++){
            macierzB[i][j] = stoi(buf2[licznik]);
            licznik++;
        } 
    }
    #ifdef WYPISZ
        for(int i = 0; i < wierszeB; i++){
            for(int j = 0; j < kolumnaB; j++){
                cout << macierzB[i][j] << ' ';
            } 
            cout << endl;
        }
        cout << "--------------------" << endl;
    #endif    
    #ifdef DEBUG
        cout << endl << wierszeB << " " << kolumnaB << endl;  
    #endif
    buf2.clear();


//---------------------|KONIEC WCZYTYWANIA MACIERZY B|------------------------

//---------------------|DEFINICJA MACIERZY C I MNOZENIE MACIERZY A PRZEZ MACIERZ B|--------------------------------
int macierzC[wierszeA][kolumnaB];

if(wierszeB != kolumnaA){
    cout << "Nie mozna przemnozyc macierzy";
    exit(EXIT_FAILURE);
}
//przejsie przez wszystkie elementy macierzy C;
    for(int i = 0; i < wierszeA; ++i){ 
        for(int j = 0; j < kolumnaB; ++j){
            int wynik = 0;
            for(int k = 0; k < kolumnaA; k++){ //moze byc tez wierszB, bo te wartosci musza by rowne sobie, aby moc przemnozyc macierz;
                wynik += macierzA[i][k] * macierzB[k][j];
            }

            macierzC[i][j] = wynik; 

        }
    }
    #ifdef WYPISZ
        for(int i = 0; i < wierszeA; i++){
            for(int j = 0; j < kolumnaB; j++){
                cout << macierzC[i][j] << ' ';
            } 
            cout << endl;
        }
        cout << "--------------------" << endl;
    #endif 
//--------------------|KONIEC MNOZENIA MACIERZY C|--------------------

//--------------------|ZAPIS MACIERZY C W PLIKU|----------------------

filein.open("./mC.txt", ios::out);

if(!filein){
    perror("Blad przy otwieraniu pliku");
    exit(EXIT_FAILURE);
}

for(int i = 0; i < wierszeA; i++){
    for(int j = 0; j < kolumnaB; j++){
        filein << macierzC[i][j] << ' ';
    } 
    if(i != (wierszeA - 1)){filein << '\n';}
}

filein.close();

}