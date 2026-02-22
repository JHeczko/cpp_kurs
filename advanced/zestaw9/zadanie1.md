# Objaśnij działanie inteligentnych wskaźników: shared_ptr, unique_pt

## Wyjasnienie
Podczas uzywania dynamiczne zaalokowanych wskaznikow, mozemy bardzo latwo zapomniec potem ich zdealokowac przy pomocy `delete`, i w ten sposob zrobic `memory leak`. Aby tego uniknac i zostawic programowi martwienie sie o pamiec, powstaly unique pointery. Maja one za zadanie automatycznie zdealokowac dynamicznie przydzielona pamiec, kiedy wyjdziemy poza "scope funkcji" lub kiedy przestaniemy juz wskazywac na podany wskaznik, gdziekolwiek w programie. 

### `unique_pt`
Jest to pointer, ktory domyslnie nie posiada konsutrktora kopiujacego. W tym podejsciu jeden `unique_pointer`, powinien wskazywac na jeden obszar w pamieci i on sobie nim zarzadza. Jest pamieciowo jak i szybkoscia zblizony do normalnego pointera, przez fakt, ze jedyna zmienna jaka ma, to zmienna do samego w sobie pointera.

### `shared_pt`
Tutaj jest inaczej, bo poza wskaznikiem do podanego obszaru pamieci, mamy rowniez, wskaznik do wspolnego licznika referencji, dla tej konkretnej grupy `shared_pointerow`. A wiec tutaj domyslnie juz jest operator kopiujacy, i mozemy miec kilka pointerow wskazujacych na ten sam obszar pamieci. Za pierwszym razem kiedy przypisujemy wskaznik pod nasz wskaznik inteligentny, to zwiekszamy licznik referencji, za kazdym razem jak robimy kopie, to wskaznik ten sie zwieksza, albo za kazdym razem jak dany obiekt wskaznika inteligentnego jest usuwany, to odejmujemy jeden z licznika referencji. Jesli dojdziemy do zera, pamiec jest zwalniana
