#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

class Obserwator{
    public:
        Obserwator(const char* cos) : nazwa(cos ? cos: "NULLPTR"){}; 
        virtual ~Obserwator(){} // nic nie robi, bo klasa bazowa
        virtual void update() = 0; // metoda czysto wirtualna
        const char* id() const {
            return nazwa.c_str();
        }
    private:
        string nazwa;
};

class Menager{
    public:
        void dodaj(unique_ptr<Obserwator> &);
        void usun(unique_ptr<Obserwator> &);
        void powiadom();
        void obserwatorzy() const;
    private:
        list<unique_ptr<Obserwator>> klient;//tutaj na przyklad na unqie ptr trzeba zmienic
};

void Menager::obserwatorzy() const{
    if(klient.empty()){
        cout << "Pusta lista / brak obserwatorow\n";
    }
    auto it = klient.cbegin(); //dlatego ze nasza metoda jest stala i podobno deduckja typu cos zle ywkrywje i bedzie blad
    while(it != klient.cend()){
        cout << "Obserwator: " << (*it)->id() << endl;
        ++it;
    }
};

void Menager::powiadom(){
    for(auto& p : klient){
        p->update();
    }
};

void Menager::dodaj(unique_ptr<Obserwator> & p){
    auto d = find(klient.begin(), klient.end(), p);
    if(d == klient.end()){
        klient.push_back(std::move(p));
    }
    else{
        cout << "Element juz jest na liscie\n";
    }
};

void Menager::usun(unique_ptr<Obserwator> & p){
    auto d = find(klient.begin(), klient.end(), p);
    if(d == klient.end()){
        cout << "Brak wskazanego elemtentu na liscie\n";
    }
    else{
        klient.erase(d);
    }
};


class Meteo : public Menager{
    public:
        double getT() const {return t;};
        void operator()(size_t n);
    private:
        double t{0.0};
        double losuj(double a, double b); //przedzial od a do b
        random_device rd; // ten obiekt do losowego pisania
};

double Meteo::losuj(double a, double b){
    mt19937 gen(rd());
    uniform_real_distribution<> dis(a,b);
    return dis(gen);
}

void Meteo::operator()(size_t n){
    for(int i = 0; i<n;++i){
        t = losuj(5,25);
        powiadom();
    }
}

class Monitor : public Obserwator{
    public:
        Monitor(const char* s, const Meteo& r) : Obserwator(s), ref(r){};
        virtual void update() override final{
            t = ref.getT();
            cout << "Obserwator: " << id() << " t = " << t << endl;
        }; // overide final nikt nie bedzie juz dziedziczyl tej metody virtualnej
    private:
        double t{0.0};
        const Meteo& ref;
};

class MonitorSredni : public Obserwator{
    public:
        MonitorSredni(const char* s, const Meteo& r) : Obserwator(s), ref(r){}; 
        void update(){
            vec.push_back(ref.getT());
            tsr = 0.0;
            for(const auto& d : vec){
                tsr += d;
            }
            tsr /= vec.size();
            cout << "Obserwator: " << id() << " Srednia: " << tsr <<endl;
        };
    private:
        double tsr{0.0};
        vector<double> vec;
        const Meteo& ref;
};

int main(){
    Meteo stacja;
    unique_ptr<Obserwator> ptr1(new Monitor("Monitor 1", stacja));
    unique_ptr<Obserwator> ptr2(new Monitor("Monitor 2", stacja));
    unique_ptr<Obserwator> ptr3 (new MonitorSredni("Monitor sredni 1", stacja));
    unique_ptr<Obserwator> ptr4 (new MonitorSredni("Monitor sredni 2", stacja));

    stacja.obserwatorzy();
    stacja.dodaj(ptr1);
    stacja.dodaj(ptr2);
    stacja.dodaj(ptr3);
    stacja.dodaj(ptr4);

    stacja.obserwatorzy(); // lista nazw obserwatorow

    stacja(2); // przeciarzany () i dwa losowania tempratur

    stacja.dodaj(ptr1); //jesli jest p1 na liscie to napisz ze jest

    stacja.usun(ptr3); // usuwamy ptr3 z listy

    stacja(2);


}