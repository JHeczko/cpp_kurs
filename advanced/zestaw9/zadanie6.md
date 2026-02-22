# Jakie jest działanie std::weak_ptr ? Przedstaw przykład użycia.

## `weak_ptr`
Rozni sie on tym od `shared_ptr`, ze nie jest on "wlasniosciowym" wksaznikiem. W praktyce oznacza to tyle, ze nie zwieksza ilosc referencji do obiektu, na ktory wskazuje. Zostal stworzony po to, aby zapobiegac, tak zwanym cyklicznym referencja, ktore sprawialy, ze pomimo zastosowania `shared_ptr`, licznik referencji nigdy nie spadl, do zera, co skutkuje wyciekiem pamieci oraz nie usunieciem tych `shared_ptr`. Oto przyklad dla zwizualizowania:

```c++
struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;  // cykl!
    Node(const std::string& n) : name(n) {}
};

int main() {
    auto a = std::make_shared<Node>("A");
    auto b = std::make_shared<Node>("B");

    a->next = b;
    b->prev = a;

    return 0; // Pamięć nie zostanie zwolniona, bo a <-> b
}
```

Aby to naprawic wystarczy jedna prosta zmiana w strukturze Node:
```c++
struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // <--- Zmiana tutaj
    Node(const std::string& n) : name(n) {}
};

int main() {
    auto a = std::make_shared<Node>("A");
    auto b = std::make_shared<Node>("B");

    a->next = b;
    b->prev = a;

    return 0;
}
```