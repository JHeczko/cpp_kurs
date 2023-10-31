#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

void transform(int, string*, std::map<int, char>);

int main(int argc, char *argv[]){
    if(argc != 2){
        perror("To many arguments");
        return -1;
    }
    int liczba = stoi(argv[1]);
    std::string rzymskie;
    std::map<int, char> znaki;

    znaki[1] = 'I';
    znaki[5] = 'V';
    znaki[10] = 'X';
    znaki[50] = 'L';
    znaki[100] = 'C';
    znaki[500] = 'D';
    znaki[1000] = 'M';

    if (liczba < 0 or liczba > 3999){
        perror("WRONG INPUT");
        return -1;
    }
    transform(liczba, &rzymskie, znaki);
    cout << rzymskie;
}

void transform(int liczba, string *output, std::map<int, char> znaki){
    switch(int i = std::floor(liczba / 1000); i)
    {
    case 4:
        break;
    case 9:
        break;
    default:
        for(int j = 0; j < i; ++j){
            *output += znaki[1000];
        }
        liczba = liczba - i*1000;
        break;
    }


    switch(int i = std::floor(liczba / 100); i)
    {
    case 9:
        *output += znaki[100];
        *output += znaki[1000];
        liczba = liczba - i*100;
        break;
    case 8:
    case 7:
    case 6:
    case 5:
        *output += znaki[500];
        for(int j = 0; j < i - 5; ++j){
            *output += znaki[100];
        }
        liczba = liczba - i*100;
        break;
    case 4:
        *output += znaki[100];
        *output += znaki[500];
        liczba = liczba - i*100;
        break;
    default:
        for(int j = 0; j < i; ++j){
            *output += znaki[100];
        }
        liczba = liczba - i*100;
        break;
    }


    switch(int i = std::floor(liczba / 10); i)
    {
    case 9:
        *output += znaki[10];
        *output += znaki[100];
        liczba = liczba - i*10;
        break;
    case 8:
    case 7:
    case 6:
    case 5:
        *output += znaki[50];
        for(int j = 0; j < i - 5; ++j){
            *output += znaki[10];
        }
        liczba = liczba - i*10;
        break;
    case 4:
        *output += znaki[10];
        *output += znaki[50];
        liczba = liczba - i*10;
        break;
    default:
        for(int j = 0; j < i; ++j){
            *output += znaki[10];
        }
        liczba = liczba - i*10;
        break;
    }


     switch(int i = std::floor(liczba / 1); i)
    {
    case 9:
        *output += znaki[1];
        *output += znaki[10];
        liczba = liczba - i*1;
        break;
    case 8:
    case 7:
    case 6:
    case 5:
        *output += znaki[5];
        for(int j = 0; j < i - 5; ++j){
            *output += znaki[1];
        }
        liczba = liczba - i*1;
        break;
    case 4:
        *output += znaki[1];
        *output += znaki[5];
        liczba = liczba - i*1;
        break;
    default:
        for(int j = 0; j < i; ++j){
            *output += znaki[1];
        }
        liczba = liczba - i*1;
        break;
    }
}