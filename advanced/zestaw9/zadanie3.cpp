/*
*3. Zaimplementuj szablon funkcji SongFactory
* tak aby obiekt ‘song’ był wskaźnikiem typu unique_ptr
* dla obiektów klasy Song
*
* auto song = SongFactory(L"Michael Jackson", L"Beat It");
*
* oraz przedstaw działanie konstruktora i destruktora obiektu przechowywanego
* przez wskaźnik we wnętrzu inteligentnego wskaźnika. Wypełnij
* std::vector<std::unique_ptr<Song>> songs i pokaż, że zakresowa pętla „for”
* musi wykorzystywać referencje.
* */

#include <iostream>
#include <memory>

using namespace std;

struct Song{
  string name;
  string artist;

  Song(string name, string artist):name(name), artist(artist){
    cout << "Witam z " << this->name << endl;
  }

  ~Song(){
    cout << "Kasacja z " << this->name << endl;
  }
};

unique_ptr<Song> songFactory(string name, string artist){
  return make_unique<Song>(name, artist);
};

int main() {
  vector<unique_ptr<Song>> songs;

  cout << "<<<<<< KONSTRUKTORY >>>>>>\n\n";
  songs.push_back(songFactory("Song1", "Artist1"));
  songs.push_back(songFactory("Song2", "Artist2"));
  songs.push_back(songFactory("Song3", "Artist3"));
  songs.push_back(songFactory("Song4", "Artist4"));
  songs.push_back(songFactory("Song5", "Artist5"));
  songs.push_back(songFactory("Song6", "Artist6"));
  songs.push_back(songFactory("Song7", "Artist7"));



  // for(auto a : songs) {
  //
  // }
  cout << "\n\n<<<<<< LOOP >>>>>>\n\n";
  for(auto& a : songs) {
    cout << "Pozdro od " << a->name << endl;
  }

  cout << "\n\n<<<<<< DESTRUKTORY >>>>>>\n\n";
  return 0;
}