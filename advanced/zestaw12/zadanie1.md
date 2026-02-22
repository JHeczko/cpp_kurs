# Singleton
**Opis i funkcja wzorca:**
Kreacyjny wzorzec ten zapewnia, ze klasa ma tylko jedna instancje w calym kodzie, ponadto jest ona dostepna grlobalnei. Ma pryawtny konstruktor

**Zastosowanie i problemy, które rozwiązuje:**

* Gwarantuje istnienie jednej instancji klasy.
* Umożliwia centralne zarządzanie stanem aplikacji.
* Zapobiega mnożeniu się obiektów, które powinny być unikalne (np. menedżer okien, konfiguracja systemu).

**Typowe przypadki użycia:**

* Systemy logowania (Logger)
* Klasy zarządzające konfiguracją
* Połączenia z bazą danych
* Sterowniki urządzeń

**Implementacja w C++:**

```c++
#include <iostream>
#include <mutex>

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // bezpieczny wątkowo od C++11
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

    // Usuwanie konstruktorów kopiujących i operatorów przypisania
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {
        std::cout << "Singleton constructor\n";
    }
};

// Przykład użycia
int main() {
    Singleton& logger1 = Singleton::getInstance();
    Singleton& logger2 = Singleton::getInstance();

    logger1.log("Pierwszy komunikat");
    logger2.log("Drugi komunikat");

    // Sprawdzenie, czy obie referencje wskazują na ten sam obiekt
    if (&logger1 == &logger2) {
        std::cout << "To ta sama instancja" << std::endl;
    }

    return 0;
}
```

**Zalety:**

* Prosta kontrola instancji
* Globalny dostep do jednej instancji
* Oszczędność zasobów, obiekt jest inicjalizowany dopiero wtedy kiedy to konieczne
* Zapewnienie spójności danych

**Wady:**

* Łamie zasade pojedynczej odpowiedzialnosci
* Trzeba uwazac w srodowisku wielowatkowym, zeby nie tworzyc wielu roznych instancji
* Moze sie zdarzyc, ze zamaskujemy nieporzadane wlasciwosci, np.: komponenty beda wiedziec o sobie za duzo
* Trudniejszy do testowania (np. w testach jednostkowych, bo wiele testow bazuje na dziedziczeniu i robieniu obiektow atrap, a tutaj brak konstrukroa publicznego/chronionego wiec nie ma jak, ale mozna jakos to ominac, choc trzeba sie nagimnastykowac)
* W niektórych przypadkach może wprowadzać problemy z zarządzaniem cyklem życia obiektu

> [!NOTE] Pojedyncza odpowiedzalnosc
> Mowi, o tym, ze kazda klasa ma spelniac tylko jedno zadanie, kazda klasa ma wiec
> 1. jeden okreslony jasno cel
> 2. Jest latwiejsza do przetestowania i utrzymania
> 3. Moze ewoluowac niezaleznie