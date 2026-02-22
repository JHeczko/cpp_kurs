#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <list>
using std::list;

#include <forward_list>
using std::forward_list;

#include <iterator>
using std::iterator_traits;
using std::forward_iterator_tag;
using std::random_access_iterator_tag;
using std::bidirectional_iterator_tag;


template <typename Iter>
int operacja_impl(Iter i, forward_iterator_tag)
{
	cout << "Iterator gorszy niż dwukierunkowy.\n";
	return 1;
}

template <typename Iter>
int operacja_impl(Iter i, bidirectional_iterator_tag)
{
	cout << "Iterator dwukierunkowy (albo lepszy).\n";
			return 2;
}

template <typename Iter>
int operacja_impl(Iter i, random_access_iterator_tag)
{
	cout << "Iterator o swobodnym dostepie.\n";
		 return 2;
}



template <typename Iter>
inline int operacja(Iter i)
{
	return operacja_impl(i,
					typename iterator_traits<Iter>::iterator_category());
}


int main()
{
	list<int> l;
	operacja(l.begin());

	int t[3];
	operacja(t);

	forward_list<int> fl;
	operacja(fl.begin());

	return 0;
}