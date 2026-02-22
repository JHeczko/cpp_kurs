/*
 * Przeanalizuj przykład zaczynający się od pliku glowny.cpp.
 * Zamienia on nazwy zrozumiałe dla człowieka ("czarny", "zielony") na strukturki ze składowymi RGB, wykorzystując do tego celu fabrykę kolorów.
 * Domyślną reakcją fabryki na przekazanie nieznanej nazwy koloru powinno być rzucenie wyjątkiem, ale chcemy zachować możliwość zmiany tej defaultowej reakcji;
 * wprowadzono więc klasę wytycznych. Zwróć uwagę na podział tego projektu na poszczególne pliki źródłowe.
 * Zaimplementuj w odrębnym pliku (albo plikach) alternatywną politykę, która zamiast wyjątku zwraca pewien ustalony kolor domyślny.
 * Przerób ją następnie z klasy na szablon klasy tak, aby można było zadawać kolor domyślny jako trzy parametry tego szablonu.
*/

#include <iostream>
using std::cin;
using std::cout;

class MojaPolityka
{
public:
	static std::string nieznanyKolor(std::string nazwa)
	{ return "Domyslny kolor"; }
};

class DefaultPolityka{
  public:
	static std::string nieznanyKolor(std::string nazwa)
	{ throw std::runtime_error("Jakis blad");; }
};

template<class WyjatekKlasa = DefaultPolityka>
class FabrykaKolorow{
	public:
          std::string zwrocKolor(std::string nazwa){
            bool bad = true;

            if(bad){
            	return WyjatekKlasa::nieznanyKolor(nazwa);
            }
          }
};

FabrykaKolorow<> fabryka;
FabrykaKolorow<MojaPolityka> moja_fabryka;

int main()
{
	try {
		cout << fabryka.zwrocKolor("zielony") << '\n';
		cout << fabryka.zwrocKolor("green") << '\n';
	} catch(...) {
		cout << "Zlapano wyjatek.\n";
	}

	cout << moja_fabryka.zwrocKolor("zielony") << '\n';
	cout << moja_fabryka.zwrocKolor("green") << '\n';

}
