#include <iostream>
#include <string>
// Klasy bazowe

using namespace std;

string conv(bool a){
    if(a){return "Tak";}
    else{return "Nie";}
}

class MozeWykBadania{
    public:
        MozeWykBadania(bool a) : wykBadania(a){};
        virtual void mozeBadania() const{
            cout << "Czy moge wykonywac badania?: "<< conv(wykBadania) << endl;
        };
    private:
        bool wykBadania;
};

class MozeNauczac{
    public:
        MozeNauczac(bool b) : Nauczac(b){};
        virtual void mozeNauczac() const{
            cout << "Czy moge wykonywac badania?: " << conv(Nauczac) << endl;
        };
    private:
        bool Nauczac;
};

class TOsoba{
    public:
        TOsoba(string a) : imie(a){};  
        virtual void mojeImie() const{
            cout << "Moje imie to: " << imie << endl;
        };
    private:
        string imie;
};

class MozeBycStudentem{
    public:
        MozeBycStudentem(bool a) : bycStudent(a){};
        virtual void mozeStudent() const{
            cout << "Czy moze byc studentem?: " << conv(bycStudent) << endl;
        };
    private:
        bool bycStudent;
};

// Koniec klas bazowych

//Lewa gałąz

class TAsystentBadan : public MozeWykBadania , virtual public TOsoba{
    public:
        TAsystentBadan(string s, bool a, bool b) : MozeWykBadania(a) , asystent(b), TOsoba(s){}; 
        virtual void czyAsystent() const{
            cout << "Czy jestem asystentem badan??: " << conv(asystent) << endl;
        };
    private:
        bool asystent;
};

class TDoktorantBadacz : public TAsystentBadan{
    public:
        TDoktorantBadacz(bool a, bool b, bool c, string s) : TAsystentBadan(s, a, b) , TOsoba(s), doktorBadacz(c){};
        virtual void czyDoktorantBadacz() const{
            cout << "Czy jestem doktorantem badaczem?: " << conv(doktorBadacz) << endl; 
        }
    private:
        bool doktorBadacz;
};

//koniec lewej galezi

//Prawa galąz

class TStudent : virtual public TOsoba , public MozeBycStudentem {
    public:
        TStudent(bool a, bool b, string imie) : student(a) , TOsoba(imie), MozeBycStudentem(b) {};
        virtual void czyStudent() const{
            cout << "Czy jestem studentem?: " << conv(student) << endl;
        }
    private:
        bool student;
};

class TDoktorant : public TStudent{
    public:
        TDoktorant(bool a, bool b, bool c, string imie) : TStudent(a,b,imie) , TOsoba(imie), doktorant(c){};
        virtual void czyDoktorant() const{
            cout << "Czy jestem doktorantem?: " << conv(doktorant) << endl;
        }
    private:
        bool doktorant;
};

class TDoktorantNaucz : public TDoktorant , public MozeNauczac{
    public:
        TDoktorantNaucz(bool a, bool b, bool c, bool d, string imie) : TDoktorant(a,b,c,imie) , doktorNaucz(d) , TOsoba(imie), MozeNauczac(c){};
    private:
        bool doktorNaucz;
};

int main(){
    TAsystentBadan Zenek("Zenek", false, true);
    Zenek.czyAsystent();
    Zenek.mojeImie();
    Zenek.mozeBadania();

    cout << endl;

    TDoktorant Marta(true, true ,false, "Marta");
    Marta.czyDoktorant();
    Marta.czyStudent();
    Marta.mojeImie();
    Marta.mozeStudent();

    cout << endl; 

    TStudent Marek(true, false, "Marek");
    Marek.czyStudent();
    Marek.mojeImie();
    Marek.mozeStudent();

    cout << endl;

    TDoktorantNaucz bratZenka(true, false, false, true, "Brat Zenka");
    bratZenka.czyDoktorant();
    bratZenka.czyStudent();
    bratZenka.mojeImie();
    bratZenka.mozeNauczac();
    bratZenka.mozeStudent();
}