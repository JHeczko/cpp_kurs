//
// Created by Jakub Heczko on 02/06/2025.
//

#include <iostream>

class Singleton{
  public:
    static Singleton& get_instance(){
      static Singleton instance;
      return instance;
    };

    void print(){
      std::cout<<"metoda niestatyczna"<<std::endl;
    }

    Singleton(Singleton& cos) = delete;
    Singleton& operator=(Singleton& cos) = delete;

    private:
      Singleton(){
        std::cout << "Singleton constructor" << std::endl;
      }
};

int main(){
  Singleton& singleton = Singleton::get_instance();
  singleton.print();

  Singleton& singleton2 = Singleton::get_instance();
  singleton2.print();
}