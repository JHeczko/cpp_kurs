#include <iostream>
#include <list>

using namespace std;

template<class InputIterator, class T> T accumulate(InputIterator first, InputIterator last, T init) {
	T total = init;
        for(InputIterator it = first; it != last; ++it){
          total += *it;
        }
    return total;
};

int main(){
	std::list<int> lista = {12,3,4,5,6};
	int total = 0;

	for(std::list<int>::iterator it = lista.begin(); it != lista.end(); it++) {
		total += *it;
	}
	cout << total << endl;

	cout << accumulate(lista.begin(), lista.end(), 0) << endl;
}