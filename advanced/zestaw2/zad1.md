# Zadanie 1

## Polimorfizm dynamiczny
Inaczej polimorfizm wykonawczy, odnosi się on do mechanizmu, w którym metoda, która będzie wywołana zależy od realnego typu obiektu, a nie od typu wskaźnik, bądź referencji. Osiąga się go za pomocą funckji wirtualnych, któreg następnie przeciąża się w klasach potomnych
```c++
class Base{
    private:
     virtual void metoda1() = 0;
}

class Poli1 : public Base{
    private:
     void metoda1() override{
        cout << "Robie cos" << endl
     }
}

class Poli2 : public Base{
    private:
     void metoda1() override{
        cout << "Robie cos innego" << endl;
     }
}

int main(void){
    Poli1 cos1 = Poli1();
    Poli2 cos2 = Poli2()
    
    Base* lista = {cos1,cos2};
    
    for(Base* el : lista){
        el->metoda1();
    }
}
```

## Polimorfizm statyczny
Wykorzystaniem szablonów, do wywołania funkcji na obiektach, które mają wspólną nazwę funkcji, typ jest dedykowany podczas wywołania funkcji, podczas kompilaci

## Klasa abstrakcyjna
Klasa, której nie można zainstancjilazować. Ma metody bez definicji, tylko deklaracje

## Funkcja wirtualna
Funckja, za pomocą, która można przeciążać w potomnych klasach.