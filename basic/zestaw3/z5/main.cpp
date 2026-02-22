#include "hash-library/sha256.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

SHA256 mine(int block_number, string transactions, SHA256& previous_hash, int difficulty){
    long long int nonce = 100000000000;
    SHA256 hash;
    for(int i = 1; i < nonce; i++){    
        string text = to_string(block_number) + transactions + previous_hash.getHash() + to_string(i);
        hash(text);
        string buf = hash.getHash();
        //cout << text << endl;
        int licznik = 0;
        for(int j = 0; j < difficulty; ++j){
            if(buf[j] == '0'){
                licznik++;
                if(licznik == difficulty){
                cout << "Found hash: " << buf;
                return hash;
                }
            }
            else{
                break;
            }
        }
        hash.reset();
        buf.clear();
        text.clear();
    }
    cout << "Hash not found";
    return hash;
}

int main(int argc, char* argv[]){
    clock_t start, end;

    string teskt("Jak cos to ten tego");

    int block_number = 34;

    int difficulty;
    cout << "Podaj trundosc: " << endl;
    cin >> difficulty;

    SHA256 hash;
    SHA256 previous_hash;
    previous_hash(teskt);

    string transactions = "Jan->Kazimierz->20,Jadwiga->Gertruda->40";

    start = clock();
    hash = mine(block_number, transactions, previous_hash, difficulty);
    end = clock();
    int czas= (end-start);
    double duration = (double) (end-start)/CLOCKS_PER_SEC;
    cout << endl << "Hash został znaleziony w dokładnie " << duration;
    return 0;

}
