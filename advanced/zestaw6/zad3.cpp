#include<stdlib.h>
#include<iostream>


// ================== POLICY ==================
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

// ================== ALLOCATORS ==================
template<typename T,size_t N = 0> struct Static_table_allocator {
  typedef T rep_type[N];
  void init(rep_type &,size_t) {};
  void expand_if_needed(rep_type &,size_t) {};
  void shrink_if_needed(rep_type &,size_t) {};
  void dealocate(rep_type &){};

  static size_t size() {return N;};

};

template<typename T,size_t N > struct Dynamic_table_allocator {
  typedef T * rep_type;
  size_t _size;
  void init(rep_type &rep,size_t n) {_size=n;rep = new T[_size];};
  void expand_if_needed(rep_type &,size_t) {};
  void shrink_if_needed(rep_type &,size_t) {};
  void dealocate(rep_type &rep){delete [] rep;};

  size_t size() const {return _size;};

};

// ================== STACK ==================

template<typename T = int , size_t N = 100,
	 typename Checking_policy = No_checking_policy,
         template<typename U,size_t M>  class Allocator_policy
	 = Static_table_allocator >
class Stack {

  typedef typename Allocator_policy<T,N>::rep_type rep_type;
  rep_type  _rep;
  size_t _top;
  Allocator_policy<T,N> alloc;
public:
  Stack(size_t n = N):_top(0) {
    alloc.init(_rep,n);
  };

  void push(const T &val) {
    alloc.expand_if_needed(_rep,_top);
    Checking_policy::check_push(_top,alloc.size());
    _rep[_top++]=val;
  }

  void pop()              {
    Checking_policy::check_pop(_top);
    --_top;
    alloc.shrink_if_needed(_rep,_top);
  }

  const T& top()  const   {
    Checking_policy::check_top(_top);
    return _rep[_top-1];
  }

   T& top()     {
    Checking_policy::check_top(_top);
    return _rep[_top-1];
  }


  bool is_empty()         {
    return !_top;
  }

  ~Stack() {alloc.dealocate(_rep);}

};


const int n=10;

int main() {
  int n=10;
  Stack<int,0,No_checking_policy,Dynamic_table_allocator> s_no_check(n);
  Stack<int,10,Abort_on_error_policy,Static_table_allocator > s_abort(n);
  ;

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