# Struktury Danych i Złożoność Obliczeniowa - Projekt: Sprawozdanie

| Wydział Elektroniki | Kierunek: Informatyka Techniczna   |
|:-------------------------------|------------------------:|
| Grupa zajęciowa Wt 15:15       | Semestr: 2020/2021 Lato |
| Prowadzący:                    | Dr inż. Dariusz Banasiak|

| Autor |
|:-------:|
| Byczko Maciej|

## Wstęp

Zadanie projektowym było napisanie programu i zmierzenie czasu wykonywania działań na:

* Tablicy dynamicznej
* Liście dwukierunkowej
* Kopcu binarnym typu MAX
* drzewie czerwono-czarnym

Działania wykonywane na powyższych strukturach były następujące:

* Dodawanie
* Usuwanie
* Znajdowanie

## Złożoności obliczeniowe

### Ogólne informacje

Złożoność obliczeniowa jest nam potrzebna aby określić ilość zasobów potrzebnych do rozwiązania problemu obliczeniowego. 
Rozważanymi zasobami są głównie:

* Czas (Czasowa złożoność obliczeniowa)- ilość czasu potrzebna do wykonania algorytmu
* Pamięć (Pamięciowa złożoność obliczeniowa)- ilość pamięci wykorzystanej w celu realizacji algorytmu

### Złożoność tablicy dynamicznej

| Funkcja | Średnia | Pesymistyczna |
|:--------|:-------:|:-------------:|
|Dodawanie| $O(n)$  |    $O(n)$     |
|Usuwanie | $O(n)$  |    $O(n)$     |
|Znajdowanie|$O(n)$ |    $O(n)$     |

### Złożoność listy dwukierunkowej

| Funkcja | Średnia | Pesymistyczna |
|:--------|:-------:|:-------------:|
|Dodawanie| $O(-)$  |    $O(n)$     |
|Usuwanie | $O(-)$  |    $O(n)$     |
|Znajdowanie|$O(n)$ |    $O(n)$     |

### Złożoność kopca binarnego

| Funkcja | Średnia | Pesymistyczna |
|:--------|:-------:|:-------------:|
|Dodawanie| $O(1)$  |    $O(1)$     |
|Usuwanie | $O(1)$  |    $O(1)$     |
|Znajdowanie|$O(n)$ |    $O(n)$     |

### Złożoność drzewa czerwono-czarnego

| Funkcja   |   Średnia  |Pesymistyczna|
|:----------|:----------:|:-----------:|
|Dodawanie  |$O(\log(n))$|$O(\log(n))$ |
|Usuwanie   |$O(\log(n))$|$O(\log(n))$ |
|Znajdowanie|$O(\log(n))$|$O(\log(n))$ |

## Plan eksperymentu

### Informacje ogólne

* Przyjęte rozmiary struktur: `1000, 2000, 5000, 10000, 20000`
* Funkcja mierząca czas: `std::chrono::high_resolution_clock`
* Sposób generacji struktur:
  * Tworzenie struktury z losowymi danymi o podanym rozmiarze
  * Wykonanie operacji mierzonej
  * Zapisanie wyniku do pliku
  * Powtórzenie operacji (wartość zadana przez użytkownika)

### Pomiary czasowe

Pomiar czasowe były mierzone w **nanosekundach** $(1 [ns] = 1 · 10−9
[s])$ za pomocą następującej funkcji:

```cpp
template<typename T>
double Timer(T i) {
auto start = chrono::high_resolution_clock::now();// Start the counter
i();// our function
auto end = chrono::high_resolution_clock::now();// Get value after executing function
auto duration = end - start;// get time difference
auto elapsed_time = chrono::duration_cast<chrono::nanoseconds> (duration).count();// calculate time 
return elapsed_time;// Return executing time in nanoseconds
}
```

## Wyniki wykonanych eksperymentów

### Pomiary tablicy dynamicznej

#### Wyniki pomiarów tablicy

|    |Liczba danych | Dodawanie na początek | Dodawanie na koniec | Dodawanie gdziekolwiek | Usuwanie początek | Usuwanie koniec | Usuwanie gdziekolwiek | Szukanie |
|----|--------------|-----------------------|---------------------|------------------------|-------------------|-----------------|-----------------------|----------|
|L.p.|      j       |           $[ns]$      |           $[ns]$    |           $[ns]$       |          $[ns]$   |          $[ns]$ |          $[ns]$       |   $[ns]$ |
| 1  | a|a | a|a | a| a| a| a |

#### Wykres dodawania elementu z przodu tablicy

![arrayAddFront]()

#### Wykres dodawania elementu z tyłu tablicy

![arrayAddBack]()

#### Wykres dodawania elementu gdziekolwiek w tablicy

![arrayAddAnywhere]()

#### Wykres usuwania elementu z przodu tablicy

![arrayRemoveFront]()

#### Wykres usuwania elementu z tyłu tablicy

![arrayRemoveBack]()

#### Wykres usuwania elementu gdziekolwiek w tablicy

![arrayRemoveAnywhere]()

#### Wykres znajdowania elementu w tablicy

![arrayFind]()

#### Wnioski na temat tablicy

Czas wykonywania operacji wzrastał wraz z ilością elementów w tablicy, więc czas potrzebny na dodawanie, usuwanie bądź
znajdowanie elementu zależy od wielkości tej struktury. Wykresy są w większości funkcją liniową.

### Pomiary listy dwukierunkowej

#### Wyniki pomiarów listy

|    |Liczba danych | Dodawanie na początek | Dodawanie na koniec | Dodawanie gdziekolwiek | Usuwanie początek | Usuwanie koniec | Usuwanie gdziekolwiek | Szukanie |
|----|--------------|-----------------------|---------------------|------------------------|-------------------|-----------------|-----------------------|----------|
|L.p.|      j       |           $[ns]$      |           $[ns]$    |           $[ns]$       |          $[ns]$   |          $[ns]$ |          $[ns]$       |   $[ns]$ |
| 1  | a|a | a|a | a| a| a| a |

#### Wykres dodawania elementu z przodu listy

![listAddFront]()

#### Wykres dodawania elementu z tyłu listy

![listAddBack]()

#### Wykres dodawania elementu gdziekolwiek w liście

![listAddAnywhere]()

#### Wykres usuwania elementu z przodu listy

![listRemoveFront]()

#### Wykres usuwania elementu z tyłu listy

![listRemoveBack]()

#### Wykres usuwania elementu gdziekolwiek w liście

![listRemoveAnywhere]()

#### Wykres znajdowania elementu w liście

![listFind]()

#### Wnioski na temat listy

coś tu będzie.

### Pomiary kopca binarnego

#### Wyniki pomiarów kopca

|    |Liczba danych | Dodawanie|Usuwanie| Szukanie |
|----|--------------|----------|--------|----------|
|L.p.|      j       |  $[ns]$  | $[ns]$ |   $[ns]$ |
| 1  | a|a | a|a | a| a| a| a |

#### Dodawanie elementu w kopcu

![heapAdd]()

#### Usuwanie elementu w kopcu

![heapRemove]()

#### Znajdowanie elementu w kopcu

![heapFind]()

### Pomiary drzewa czerwono-czarnego

#### Wyniki pomiarów drzewa

|    |Liczba danych | Dodawanie|Usuwanie| Szukanie |
|----|--------------|----------|--------|----------|
|L.p.|      j       |  $[ns]$  | $[ns]$ |   $[ns]$ |
| 1  | a|a | a|a | a| a| a| a |

#### Dodawanie elementu w drzewie

![treeAdd]()

#### Usuwanie elementu w drzewie

![treeRemove]()

#### Znajdowanie elementu w drzewie

![treeFind]()

#### Wnioski na temat drzewa

Coś tu będzie.

## Wnioski końcowe

Tutaj musi coś być.
