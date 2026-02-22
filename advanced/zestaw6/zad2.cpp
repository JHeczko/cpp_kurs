#include<stdlib.h>
#include<iostream>

struct No_checking_policy {
  static void check_push(size_t,size_t) {};
  static void check_pop(size_t) {};
  static void check_top(size_t) {};
};

struct Abort_on_error_policy {
  static void check_push(size_t top,size_t size) {

    if(top >= size) {
      std::cerr<<"trying to push elemnt on full stack: aborting"<<std::endl;
      abort();
    }
  };

  static void check_pop(size_t top) {
      if(top == 0) {
      std::cerr<<"trying to pop an empty stack: aborting"<<std::endl;
      abort();
      }
  };
  static void check_top(size_t top) {
      if(top == 0) {
      std::cerr<<"trying to read from empty stack: aborting"<<std::endl;
      abort();
      }
  };
};


template<typename T = int , size_t N = 100,
	 typename Checking_policy = No_checking_policy >
class Stack {
  T  _rep[N];
  size_t _top;
public:
  Stack(size_t n = N):_top(0) {};

  void push(const T &val) {
    Checking_policy::check_push(_top,N);
    _rep[_top++]=val;
  }

  void pop()              {
    Checking_policy::check_pop(_top);
    --_top;
  }

  const T top()  const   {
    Checking_policy::check_top(_top);
    return &_rep[_top-1];
  }

   T &top()     {
    Checking_policy::check_top(_top);
    return _rep[_top-1];
  }


  bool is_empty()         {
    return !_top;
  }

};

const int n=10;

int main() {
	Stack<int,10> s_no_check;
	Stack<double ,100,Abort_on_error_policy> s_abort;

  int iter = 0;
  while(true){
    s_no_check.push(10);
    if (iter == 40){
      break;
    }else {
      ++iter;
    }
  }

  std::cout << "Stopped: no abbort\n";
  std::cout.flush();

  while(true){
    s_abort.push(10);
  }

}