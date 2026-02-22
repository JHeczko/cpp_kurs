//
// Created by Jakub Heczko on 25/03/2025.
//

# include <iostream>
#include <typeinfo>

using namespace std;

template<typename T, typename U> T convert(U a){
  return static_cast<T>(a);
}

template<> double convert<double, int>(int a){
  return static_cast<double>(a);
}

template<> float convert<float,int>(int a){
  return static_cast<float>(a);
}

int main(){
  int a = 1;
  cout << typeid(convert<double>(a)).name() << endl;
  cout << typeid(convert<float>(a)).name() << endl;
}