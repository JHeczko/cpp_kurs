# include <iostream>

using namespace std;

template<typename T> T max(T a, T b){
  return (a > b) ? a : b;
}

template<typename T> T* max(T* a, T* b){
  return ((*a)>(*b))?a:b;
}

template<typename T> T max(T* data, size_t n){
  T _max = data[0];
  for(size_t i=0;i<n;i++)
    if(data[i]>_max) _max=data[i];
  return _max;
}

template<> char* max(char* a, char* b){
  return (strcmp(a,b)>0)?a:b;
}

template<> const char* max(const char* a, const char* b){
  return (strcmp(a,b)>0)?a:b;
}

template<typename T>  const T* max(T* a,const T* b){
  return (*a)>(*b)?a:b;
}

template<> const char* max(char *a,const char *b) {
  return (strcmp(a,b)>0)?a:b;
}

int main(){
  int a = 32;
  int b = 42;

  char e = 'b';
  char f = 'a';


  const char* c = "Jeqweqw";
  const char* d = "Kewqeqw";

  char str1[] = "cos tam";
  char str2[] = "cos tam2";

  int data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  size_t size = sizeof(data)/sizeof(data[0]);

  cout << ::max<int>(a,b) << endl;
  cout << *(::max<int>(&a, &b)) << endl;
  cout << (::max<const char*>(c, d)) << endl;
  cout << ::max(str1,str2) << endl;
  cout << *(::max<char*>(&e, &f)) << endl;
  cout << ::max<int>(data, size) << endl;

}