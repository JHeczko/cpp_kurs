#include <iterator>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

template<typename T> struct sum_traits;

template<>
struct sum_traits<int> {
	typedef int sum_type;
	static sum_type zero() {
		return 0;
	}
};

template<typename IT> typename sum_traits<typename iterator_traits<IT>::value_type>::sum_type sum(IT beg,IT end) {
	typedef typename iterator_traits<IT>::value_type value_type;
	typedef typename sum_traits<value_type>::sum_type sum_type;
	sum_type total = sum_traits<value_type>::zero();
	while(beg != end ) {
		total += *beg; beg++;
	}
	return total;
}

int main()
{
	vector<int> v = {1, 2, 3, 4, 5};
	cout << "Suma elementów wektora: " << sum(v.begin(), v.end()) << endl;

	list<int> l = {6, 7, 8, 9, 10};
	cout << "Suma elementów listy: " << sum(l.begin(), l.end()) << endl;

	int arr[] = {11, 12, 13, 14, 15};
	cout << "Suma elementów tablicy: " << sum(arr, arr + sizeof(arr) / sizeof(int)) << endl;

	return 0;
}