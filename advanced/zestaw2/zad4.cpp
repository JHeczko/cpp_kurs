#include <iostream>
#include <list>
#include <functional>

using namespace std;

template<typename T> class SequenceGen{
    private:
        T _start;
        T _step;
    public:
        SequenceGen(T start, T step): _start(start), _step(step){};

        T operator()(){
          T tmp = _start;
          _start += _step;
          return tmp;
        }
};

size_t size_vec = 20;

int main(){
	std::vector<int> vec(size_vec);

	generate_n(vec.begin(),size_vec,SequenceGen<int>(1,2));

    std::vector<int>::iterator it = find_if(vec.begin(),vec.end(), std::bind2nd(std::greater<int>(), 4));

    for(;it!=vec.end();++it){
      cout << *it << endl;
    }
}