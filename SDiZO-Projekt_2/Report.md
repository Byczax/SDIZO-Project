# Struktury Danych i Złożoność Obliczeniowa - Projekt: Sprawozdanie

| Wydział Elektroniki      | Kierunek: Informatyka Techniczna |
| :----------------------- | -------------------------------: |
| Grupa zajęciowa Wt 15:15 |          Semestr: 2020/2021 Lato |
| Prowadzący:              |         Dr inż. Dariusz Banasiak |

|        Autor         |
| :------------------: |
| Byczko Maciej 252747 |

## Wstęp

Zadanie projektowym było napisanie programu i zmierzenie czasu wykonywania działań na:

- Wyznaczaniu minimalnego drzewa rozpinającego za pomocą:
  - Algorytmu Prima
  - Algorytmu Kruskala
- Najkrótszą ścieżkę w grafie:
  - Algorytm Dijkstry
  - Algorytm Bellmana-Forda

Powyższe algorytmy były wykonywane na następujących strukturach:

- Macierz sąsiedztwa - macierz o wymiarze V x V (V - Liczba wierzchołków), w której wiersz oznacza wierzchołek początkowy, kolumna wierzchołek końcowy a w punkcie wspólnym znajduje się waga krawędzi, jeżeli w punkcie wspólnym występuje 0, oznacza to że nie ma połączenia z danymi wierzchołkami.
- Lista sąsiedztwa - graf zapisany jako V list, gdzie w każdej liście są przechowywane numery wierzchołków do których można się dostać z danego wierzchołka (przykładowo na liście 2 przechowywane są wierzchołki do których można się dostać z wierzchołka 2)

### Złożoność algorytmów

#### Reprezentacja za pomocą listy następników

| Algorytm     | Złożoność czasowa |
| :----------- | :---------------: |
| Prim         |   $O(E \log V)$   |
| Kruskal      |   $O(E \log E)$   |
| Dijkstra     |   $O(E \log V)$   |
| Bellman-Ford |  $O(E \cdot V)$   |

#### Reprezentacja za pomocą macierzy sąsiedztwa

| Algorytm     | Złożoność czasowa |
| :----------- | :---------------: |
| Prim         |     $O(V^2)$      |
| Kruskal      |   $O(E \log E)$   |
| Dijkstra     |   $O(E \log V)$   |
| Bellman-Ford |  $O(E \cdot V)$   |

## Plan eksperymentu

### Informacje ogólne

- Pomiar czasu podczas wykonywania algorytmów dla następujących parametrów grafów:

  - Rozmiary grafów od 10 do 100 wierzchołków
  - Badane gęstości od 20% do 99%

- Funkcja mierząca czas: `std::chrono::high_resolution_clock`

- Sposób generacji struktur:

  - Tworzenie struktury z losowymi danymi o podanym rozmiarze (każdy pomiar miał generowaną losową strukturę z zadanymi parametrami)

  - Wykonanie operacji mierzonej

  - Zapisanie wyniku do pliku

  - Powtórzenie operacji (wartość zadana przez użytkownika)

### Generowanie grafu

Dla każdego typu algorytmu był wybierany odpowiedni typ tworzonego grafu:

- Graf nieskierowany dla algorytmu Prima oraz Kruskala:

  1. Stworzenie listy wszystkich wierzchołków
  2. Stworzenie listy wszystkich możliwych krawędzi (będzie to potrzebne w późniejszym etapie)
  3. Wylosowanie dwóch wierzchołków
  4. Utworzenie pomiędzy nimi połączenia nieskierowanego (dwustronnego) z losową wartością
  5. Usunięcie pierwszego wylosowanego wierzchołka
  6. Gdy zostaje spełniony warunek grafu spójnego (wszystkie wierzchołki są połączone) to następuje etap uzupełnienia gęstości grafu:
     1. Wylosowanie krawędzi z listy wszystkich możliwych krawędzi
     2. Utworzenie połączenia aby zastosować wylosowaną krawędź
     3. Usunięcie utworzonego połączenia z listy możliwych krawędzi
     4. Powtórzenie powyższych punktów dopóki nie zostanie spełniona gęstość grafu

- Graf skierowany dla algorytmu Dijkstry oraz Bellmana-Forda:

  1. Stworzenie listy wszystkich wierzchołków
  2. Stworzenie listy wszystkich możliwych krawędzi (będzie to potrzebne w późniejszym etapie)
  3. Utworzenie wierzchołka początkowego = 0
  4. Wylosowanie wierzchołka z wszystkich wierzchołków
  5. Utworzenie pomiędzy wierzchołkiem 0 oraz wierzchołkiem wylosowanym połączenia skierowanego z losową wartością
  6. Ustawienie wylosowanego wierzchołka na miejsce wierzchołka początkowego (na początku 0)
  7. Usunięcie wylosowanego wierzchołka z listy wszystkich wierzchołków
  8. Powtórzenie punktów 4 - 7 aż nie otrzymamy grafu spójnego
  9. Gdy zostaje spełniony warunek grafu spójnego (wszystkie wierzchołki są połączone) to następuje etap uzupełnienia gęstości grafu:
     1. Wylosowanie krawędzi z listy wszystkich możliwych krawędzi
     2. Utworzenie połączenia aby zastosować wylosowaną krawędź
     3. Usunięcie utworzonego połączenia z listy możliwych krawędzi
     4. Powtórzenie powyższych punktów dopóki nie zostanie spełniona gęstość grafu

Każda krawędź ma nadaną wartość losową z przedziału od 1 do 999.

### Pomiary czasowe

Pomiar czasowe były mierzone w **nanosekundach** $(1 [ns] = 1 * 10^9 [s])$ za pomocą następującej funkcji:

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

### Wyniki wykonanych eksperymentów

|      | Liczba wierzchołków | Gęstość | Prim - Lista | Prim - macierz | Kruskal - Lista | Kruskal - macierz |
| ---- | ------------------- | ------- | ------------ | -------------- | --------------- | ----------------- |
| L.p. | j                   | $\%$    | $[ns]$       | $[ns]$         |                 |                   |
| 1    | 20                  | 25%     |              |                |                 |                   |
| 2    | 20                  | 50%     |              |                |                 |                   |
| 3    | 20                  | 75%     |              |                |                 |                   |
| 4    | 20                  | 99%     |              |                |                 |                   |
| 5    | 2                   | 2%      |              |                |                 |                   |
| 6    | 3                   | 2%      |              |                |                 |                   |
| 7    | 3                   | 2%      |              |                |                 |                   |
| 8    | 4                   | 2%      |              |                |                 |                   |
| 9    | 4                   | 2%      |              |                |                 |                   |
| 10   | 5                   | 2%      |              |                |                 |                   |

## Wnioski końcowe

Podsumowując wykonane pomiary większość wyszła zgodnie z przewidywaniami, w niektórych miejscach mamy dziwne
przesunięcia, najprawdopodobniej jest to spowodowane:

- Słabo zoptymalizowane algorytmy

- Działanie innych programów podczas wykonywania pomiarów co spowodowało odchylenia i błędy pomiarowe

## Bibliografia

[Jarosław Mierzwa](http://jaroslaw.mierzwa.staff.iiar.pwr.wroc.pl/)

[Wikipedia - Adjacency matrix](https://en.wikipedia.org/wiki/Adjacency_matrix)

[Wikipedia - Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

[Wikipedia - Prim](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

[Wikipedia - Bellman-Ford](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

[Eduinf Waw - Reprezentacje grafów](https://eduinf.waw.pl/inf/alg/001_search/0124.php)

[Eduinf Waw - MST](https://eduinf.waw.pl/inf/alg/001_search/0141.php)

[Eduinf Waw - Bellman-Ford](https://eduinf.waw.pl/inf/alg/001_search/0138a.php)

[Eduinf Waw - Dijkstra](https://eduinf.waw.pl/inf/alg/001_search/0138.php)
