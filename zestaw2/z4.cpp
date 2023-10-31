#include <iostream>
#include <filesystem>
#include <string>


using namespace std;
using namespace filesystem;


int main (){
    string adres;
    
    cout << "Podaj adres katalogu: " << endl;
    getline(cin, adres);
    if (adres.empty()){
        cout << "No path in";
        return -1;
    }
    path sciezka(adres);
    if(!is_directory(sciezka)){
        cout << "Zla sciezka" << endl;
        return -1;
    }
    else if (filesystem::is_empty(sciezka)){
        cout << "Folder jest pusty" <<  endl;
        return 0;
    } 
    


    for(auto i : directory_iterator(sciezka)){
        path dir = i.path();
        if(status(dir).type() == file_type::regular){
            cout << "Sciezka: " << dir << " Rozmiar: " << i.file_size() << " B" << endl; 
        }

    }


    return 0;
}
