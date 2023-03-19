# Wprowadzenie
Balanced binary representation (BBR) jest pozycyjnym zapisem liczby całkowitej z podstawą 2 i cyframi -1, 0, 1. Zapis BBR liczby jest w postaci non-adjacent form (NAF) jeśli cyfry niezerowe nie sąsiadują ze sobą.

Każda liczba całkowita ma dokładnie jeden zapis BBR-NAF bez zer wiodących. Dla 0 jest on pusty. Dla niezerowego x najmniej znaczącą cyfrą c jest:

0 jeśli x jest parzyste,

1 jeśli x - 1 jest podzielne przez 4,

-1 jeśli x + 1 jest podzielne przez 4.

Bardziej znaczące cyfry zapisu x tworzą zapis liczby (x - c) / 2.

Zapis BBR-NAF minimalizuje, w klasie zapisów binarnych, wagę Hamminga liczby, czyli liczbę cyfr niezerowych. Na przykład liczby pierwsze Mersenne'a mają w tym zapisie wagę 2. Zapisu BBR-NAF używa się w kryptografii krzywych eliptycznych stosowanej, między innymi, w implementacjach kryptowaluty Bitcoin i platformy Ethereum .

Tematem zadania jest reprezentacja zapisu BBR-NAF, umożliwiająca efektywne operacje arytmetyczne na dużych liczbach całkowitych z małą wagą Hamminga.

Reprezentacja jest oparta na systemie liczbowym arithmeticæ localis , opisanym przez Johna Napiera, w 1617 roku, w traktacie Rabdologiæ. Jest to system binarny, ale nie pozycyjny, lecz addytywny.

W systemach pozycyjnych wartość liczby jest określona przez ciąg cyfr jej zapisu, z uwzględnieniem pozycji, na której cyfra występuje. W systemach addytywnych wartość liczby jest sumą wartości cyfr.

W arithmeticæ localis rolę cyfr pełnią litery, reprezentujące potęgi dwójki. W naszej reprezentacji, którą nazwiemy Napier-NAF, cyframi są liczby całkowite, które reprezentują potęgi dwójki i liczby do nich przeciwne. Reprezentacją cyfry o wartości 2 ** n jest nieujemna liczba całkowita n. Reprezentacją cyfry o wartości -(2 ** n) jest ujemna liczba całkowita -n - 1.

Reprezentacją Napier-NAF liczby całkowitej x jest tablica liczb całkowitych, której długością jest waga Hamminga zapisu BBR-NAF liczby x. W tablicy:

ujemna liczba n informuje o wystąpieniu cyfry -1 na pozycji -n - 1 zapisu BBR-NAF liczby x,

nieujemna liczba n informuje o wystąpieniu cyfry 1 na pozycji n zapisu BBR-NAF liczby x,

informacje o cyfrach są uporządkowane w kolejności od najmniej znaczących a pozycje są numerowane od 0.

# Polecenie
W pliku nagłówkowym napiernaf.h jest interfejs modułu operacji arytmetycznych na liczbach całkowitych w reprezentacji Napier-NAF:

- funkcja

`void iton(int x, int **a, int *n);` <br/>
zapisuje reprezentację liczby x w dynamicznie utworzonej *n-elementowej tablicy *a,

- funkcja

`int ntoi(int *a, int n);` <br/>
daje jako wynik wartość liczby reprezentowanej przez n-elementową tablicę a, lub 0, jeśli wartość ta nie mieści się w zakresie typu int,

- funkcja

`void nadd(int *a, int an, int *b, int bn, int **c, int *cn);` <br/>
zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c sumę liczb reprezentowanych przez an-elementową tablicę a i bn-elementową tablicę b,

- funkcja

`void nsub(int *a, int an, int *b, int bn, int **c, int *cn);` <br/>
zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c różnicę liczb reprezentowanych przez an-elementową tablicę a i bn-elementową tablicę b,

- funkcja

`void nmul(int *a, int an, int *b, int bn, int **c, int *cn);` <br/>
zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c iloczyn liczb reprezentowanych przez an-elementową tablicę a i bn-elementową tablicę b,

- funkcja

`void nexp(int *a, int an, int *b, int bn, int **c, int *cn);` <br/>
zapisuje w dynamicznie utworzonej *cn-elementowej tablicy *c wynik potęgowania, którego podstawa jest reprezentowana przez an-elementową tablicę a, a nieujemny wykładnik jest reprezentowany przez bn-elementową tablicę b,

- funkcja

`void ndivmod(int *a, int an, int *b, int bn, int **q, int *qn, int **r, int *rn);` <br/>
dzieli liczbę, której reprezentacją jest an-elementowa tablica a, przez niezerową liczbę, której reprezentacją jest bn-elementowa tablica b. Iloraz zapisuje w dynamicznie utworzonej *qn-elementowej tablicy *q. Resztę z dzielenia zapisuje w dynamicznie utworzonej *rn-elementowej tablicy *r. <br/>

Funkcja daje wynik zgodny z algorytmem dzielenia Euklidesa . Wynikiem dzielenia całkowitej liczby a przez niezerową całkowitą liczbę b jest całkowity iloraz q i całkowita reszta r, które spełniają warunki:
```
a = b * q + r,
0 <= r < abs(b),
```
gdzie abs(b) jest wartością bezwzględną liczby b.
