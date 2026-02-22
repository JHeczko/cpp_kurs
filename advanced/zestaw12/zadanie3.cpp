#include <iostream>

using namespace std;

// bazowy interfejs wiadomosci
class Messege{
  public:
    virtual string getMess()=0;
    ~Messege()=default;
};

class SimpleMessege : public Messege {
  public:
    SimpleMessege()=default;
    string getMess(){
      return "Messege";
    };
};

class BaseDecarator:public Messege {
protected:
  Messege* messege;
public:
    BaseDecarator(Messege* messege):messege(messege){};
    string getMess(){
      return messege->getMess();
    };
};

class AddBracketsDecorator:public BaseDecarator {
  public:
    AddBracketsDecorator(Messege* messege):BaseDecarator(messege){};

    string getMess(){
      return messege->getMess()+"<>";
    };
};

class AddSmthDecorator:public BaseDecarator {
  public:
    AddSmthDecorator(Messege* messege):BaseDecarator(messege){};
    string getMess(){
      return messege->getMess()+"SMTH";
    };
};


class AddSmthElseDecorator:public BaseDecarator {
public:
  AddSmthElseDecorator(Messege* messege):BaseDecarator(messege){};
  string getMess(){
    return messege->getMess()+"else";
  };
};

int main(){
  Messege* messege = new SimpleMessege();

  BaseDecarator* decorator = new BaseDecarator(messege);
  cout << decorator->getMess() << endl;

  decorator= new AddBracketsDecorator(decorator);
  cout << decorator->getMess() << endl;

  decorator = new AddSmthDecorator(decorator);
  cout << decorator->getMess() << endl;

  decorator = new AddSmthElseDecorator(decorator);
  cout << decorator->getMess() << endl;
}