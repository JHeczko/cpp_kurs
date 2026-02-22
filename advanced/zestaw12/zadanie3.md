# Dekorator
**Wzorzec projektowy Dekorator w C++**

**Opis i funkcja wzorca:**
Strukturalny wzorzec, zwany tez nakladką albo wrapperem. Charakteryzuje go to, ze pozwala on dodawac nowe funckjonalnosc/obowiazki obiektom, za pomoca umieszczania ich kolejna, jakby rekurecyjne w wrapperach, ktore dekorują go w nowe funkcjonalnosci. Poniewaz duza cczesc obiektowych jezykow, nie pozwala na dziediczenie wielkrotne, to trzeba radzic sobie za pomoca tak zwanej agregacji. Zmiany będą kaskadowo propagowane w dół

**Zastosowanie i problemy, które rozwiązuje:**

* Potrzeba dodania nowych funkcji do klasy bez dziedziczenia.
* Unikanie tworzenia dużych hierarchii klas.
* Zwiększenie elastyczności przez składanie funkcjonalności dynamicznie.

**Typowe przypadki użycia:**

* Rozszerzanie funkcjonalności GUI (np. dekorowanie komponentów)
* Logowanie, autoryzacja, buforowanie
* Kompresja / szyfrowanie danych

```c++
#include <iostream>

using namespace std;

// bazowy interfejs wiadomosci
class Messege{
  public:
    virtual string getMess()=0;
    ~Messege()=default;
};

class SimpleMessege : public Messege {
  public:
    SimpleMessege()=default;
    string getMess(){
      return "Messege";
    };
};

class BaseDecarator:public Messege {
protected:
  Messege* messege;
public:
    BaseDecarator(Messege* messege):messege(messege){};
    string getMess(){
      return messege->getMess();
    };
};

class AddBracketsDecorator:public BaseDecarator {
  public:
    AddBracketsDecorator(Messege* messege):BaseDecarator(messege){};

    string getMess(){
      return messege->getMess()+"<>";
    };
};

class AddSmthDecorator:public BaseDecarator {
  public:
    AddSmthDecorator(Messege* messege):BaseDecarator(messege){};
    string getMess(){
      return messege->getMess()+"SMTH";
    };
};


class AddSmthElseDecorator:public BaseDecarator {
public:
  AddSmthElseDecorator(Messege* messege):BaseDecarator(messege){};
  string getMess(){
    return messege->getMess()+"else";
  };
};

int main(){
  Messege* messege = new SimpleMessege();

  BaseDecarator* decorator = new BaseDecarator(messege);
  cout << decorator->getMess() << endl;

  decorator= new AddBracketsDecorator(decorator);
  cout << decorator->getMess() << endl;

  decorator = new AddSmthDecorator(decorator);
  cout << decorator->getMess() << endl;

  decorator = new AddSmthElseDecorator(decorator);
  cout << decorator->getMess() << endl;
}
```

**Zalety:**

* Elastyczne rozszerzanie funkcjonalności(usuwanie/dodawanie nowych funckjonalnosci w trakcie dzialania programu)
* Unikanie wykładniczego wzrostu liczby klas
* Możliwość łączenia wielu dekoratorów dynamicznie

**Wady:**

* Poniewaz dekoratory układają się w stos, trudne może być usunięcie środkowej funckjonalności
* Kolejność wykonania w dekaratorzy zalezy od kolejnosci na stosie
* Może prowadzić do wielu małych klas
* Zwiększona złożoność debugowania(troche trudno sie na to patrzy momentami, ale moze to tylka ja)
