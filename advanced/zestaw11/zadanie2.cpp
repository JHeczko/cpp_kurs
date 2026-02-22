/**
 * Mowiac krotko mowi nam on, ze nasze typy musza oblsugiwac operator <=>
 * Podczas kompilacji sprawdzene jest czy typ ma operator <=>, jesli nie to program sie wywala
 * Jesli ma to sprawdzane jeszcze jest sprawdzane jest czy zwracany typ jest uporzadkowany silnie,czesciowo czy slabo i czy zgadza sie to z tym co podalismy jako
 * argument do std::three_way_comparable, (domyslnie std::partial_ordering)
 */

#include <concepts>
#include <compare>
#include <iostream>

using namespace std;

template<typename T>
void three_way(T a, T b)
requires std::three_way_comparable<T>{
	auto cmp = a<=>b;
	int out;
	if (cmp < 0) {
		out = -1;
	}else if (cmp > 0) {
		out = 1;
	}else {
		out = 0;
	}
	cout << "Comparison: " << out << endl;
}

int main(){
	int a = 11;
  int b = 10;

	three_way(b,a);

	return 0;
}