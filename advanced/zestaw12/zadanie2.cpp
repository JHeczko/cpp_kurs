#include <iostream>

// interfejs subskrybujacego
class Subscriber{
  public:
    virtual void receive() = 0;
};


class MessegeManager{
private:
  std::vector<Subscriber*> subscribers;

public:
  	void notify(){
      for (Subscriber* subs:subscribers){
        subs->receive();
      }
  	}

    void attach(Subscriber* subscriber){
			subscribers.push_back(subscriber);
    };

    void detach(Subscriber* subscriber){
      subscribers.erase(std::find(subscribers.begin(), subscribers.end(), subscriber));
    };

    MessegeManager(){};
    ~MessegeManager(){};
};

class ProductMenager {
  public:
    MessegeManager* messegeManager;

    void newProductAdded() {
        // jakas logika
        messegeManager->notify();
    }

    ProductMenager():messegeManager(new MessegeManager()){}
    ~ProductMenager(){}
};

class ExtendedSubscriber:public Subscriber{
private:
  std::string name;
public:
    void receive(){
      std::cout << "Mam wiadomosc " << this->name << std::endl;
    };

    ExtendedSubscriber(std::string name):name(name){};
};

class ExtendedSubscriberEmail:public Subscriber{
private:
  std::string name;
public:
  void receive(){
    std::cout << "Mam wiadomosc email" << this->name << std::endl;
  };

  ExtendedSubscriberEmail(std::string name):name(name){};
};

int main(){
  ExtendedSubscriber* subscriber = new ExtendedSubscriber("1");
  ExtendedSubscriber* subscriber2 = new ExtendedSubscriber("2");
  ExtendedSubscriber* subscriber3 = new ExtendedSubscriber("3");
  ExtendedSubscriberEmail* subscriber4 = new ExtendedSubscriberEmail("4");

  ProductMenager* messege = new ProductMenager();

  messege->messegeManager->attach(subscriber);
  messege->messegeManager->attach(subscriber2);
  messege->messegeManager->attach(subscriber3);
  messege->messegeManager->attach(subscriber4);

  messege->newProductAdded();
}