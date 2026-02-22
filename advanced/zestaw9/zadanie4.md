# 4. Wyjaśnij zastosowanie dwóch możliwych specjalizacji dla szablonu unique_ptr

```c++
template< class T, class... Args > unique_ptr<T> make_unique( Args&&... args );

template< class T > unique_ptr<T> make_unique( std::size_t size );
```

## Wyjasnienie
|         Specjalizacja         |                                                            Wykorzystanie                                                            |
|:-----------------------------:|:-----------------------------------------------------------------------------------------------------------------------------------:|
|   make_unique<T>(Args&&...)   |                        Inicjalizajca pojedynczych obiektow klasy T, wraz z argumentami dla ich konstruktora                         |
| make_unique<T[]>(size_t size) | Sluzy do inicjalizacji tablic z podanymi obiketami klasy T, niemozliwe jest przekazanie argumentow do konstruktora, takich obiektow |

