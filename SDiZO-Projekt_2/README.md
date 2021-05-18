# SDiZO - Zadanie projektowe nr. 2

Struktury Danych i Złożoności Obliczeniowe - Projekt, część druga

## Badanie efektywności algorytmów grafowych w zależności od rozmiaru instancji oraz sposobu reprezentacji grafu w pamięci komputera.

### Polecenie

Należy zaimplementować oraz dokonać pomiaru czasu działania wybranych algorytmów grafowych rozwiązujących następujące problemy:

- wyznaczanie minimalnego drzewa rozpinającego (MST) - algorytm Prima oraz algorytm Kruskala,
- wyznaczanie najkrótszej ścieżki w grafie – algorytm Dijkstry oraz algorytm Forda-Bellmana,
- wyznaczanie maksymalnego przepływu – algorytm Forda-Fulkersona (na ocenę 5.5).

Algorytmy te należy zaimplementować dla obu poniższych reprezentacji grafu w pamięci komputera:

- reprezentacja macierzowa (macierz incydencji),
- reprezentacja listowa (lista następników/poprzedników).

### Założenia

- wszystkie struktury danych powinny być alokowane dynamicznie,
- przepustowość/koszt krawędzi jest liczbą całkowitą (dodatnią),
- po zaimplementowaniu każdego z algorytmów dla obu reprezentacji grafu należy dokonać pomiaru czasu działania algorytmów w zależności od rozmiaru grafu oraz jego gęstości (liczba krawędzi w stosunku do liczby wierzchołków).
- Badania należy wykonać dla 5 różnych (reprezentatywnych) liczb wierzchołków V oraz następujących gęstości grafu: 25%, 50%, 75% oraz 99%.
- Dla każdego zestawu: reprezentacja, liczba wierzchołków i gęstość należy wygenerować serię losowych instancji (np. 20, 50 lub 100 w zależności od rozrzutu poszczególnych wyników), zaś w sprawozdaniu umieścić wyłącznie wyniki uśrednione z danej serii,
- program powinien umożliwić sprawdzenie poprawności zaimplementowanych operacji i zbudowanej struktury grafu (dodatkowe informacje w dalszej części dokumentu),
- zalecanymi językami programowania są języki kompilowane do kodu natywnego (np. C, C++), a nie interpretowane lub uruchamiane na maszynach wirtualnych (np. JAVA, .NET, Python, w wyjątkowej sytuacji można je wykorzystać, o ile nie wpływa to istotnie na uzyskane wyniki),
- używanie okienek nie jest konieczne i nie wpływa na ocenę (wystarczy wersja konsolowa), - korzystanie z gotowych bibliotek np. STL, Boost lub innych powoduje obniżenie oceny za projekt (dotyczy to podstawowych dla projektu struktur, szczegóły zostały omówione w części dotyczącej oceny projektu),
- wszystkie algorytmy i struktury muszą być zaimplementowane samodzielnie (nie należy kopiować gotowych rozwiązań),
- implementacja projektu powinna być wykonana w formie jednego programu,
- kod źródłowy powinien być komentowany.

### Sprawdzanie poprawności

wczytanie struktury grafu z pliku tekstowego.
Plik zawiera opis poszczególnych krawędzi według wzoru:
początek krawędzi, koniec krawędzi oraz waga/przepustowość.  
Struktura pliku jest następująca:

- w pierwszej linii zapisana jest liczba krawędzi oraz liczba wierzchołków (rozdzielone spacją),
- wierzchołki numerowane są w sposób ciągły od zera,
- w kolejnych liniach znajduje się opis krawędzi (każda krawędź w osobnej linii) w formie trzech liczb przedzielonych spacjami (wierzchołek początkowy, wierzchołek końcowy oraz waga/ przepustowość),
- dla problemu MST pojedynczą krawędź traktuje się jako nieskierowaną, natomiast dla algorytmów najkrótszej drogi i maksymalnego przepływu jako skierowaną,
- losowe wygenerowanie grafu (jako dane podaje się liczbę wierzchołków oraz gęstość w procentach).
- Do przechowywania struktury grafu wczytanej z pliku lub wygenerowanej losowo należy wykorzystać tą samą zmienną/obiekt (ostatnia operacja generowania danych losowo lub wczytywania z pliku nadpisuje poprzednią),
- możliwość wyświetlenia na ekranie wczytanego lub wygenerowanego grafu w formie reprezentacji listowej i macierzowej,
- uruchomienie algorytmu dla obu reprezentacji i wyświetlenie wyników na ekranie (wyświetlane wyniki powinny w pełni reprezentować rozwiązanie danego problemu np. dla algorytmów Dijkstry oraz Forda-Bellmana należy wyświetlić zarówno znalezioną ścieżkę jak i całkowity koszt tej ścieżki).
  Dla problemu najkrótszej drogi w grafie i maksymalnego przepływu musi być możliwość podania wierzchołka początkowego i końcowego.

Poniższe operacje należy zrealizować w formie menu dla każdej struktury i dla każdego problemu z osobna:

1. Wczytaj dane z pliku.
2. Wygeneruj graf losowo.
3. Wyświetl graf listowo i macierzowo na ekranie.
4. Algorytm 1 (np. Prima) macierzowo i listowo z wyświetleniem wyników.
5. Algorytm 2 (np. Kruskala) macierzowo i listowo z wyświetleniem wyników.

## Sprawozdanie (w formie papierowej lub elektronicznej)

- krótki wstęp zawierający oszacowanie złożoności obliczeniowej poszczególnych problemów na podstawie literatury,
- plan eksperymentu czyli założenia co do wielkości struktur, sposobu generowania ich elementów, sposobu pomiaru czasu, itp.
- opis metody generowania grafu (sposób powinien zapewnić spójność oraz zmienną strukturę grafu),
- wyniki należy przedstawić w tabelach oraz w formie wykresów dla każdego problemu osobno (oddzielnie MST i najkrótsza droga w grafie).
  Dla każdego problemu (MST oraz najkrótsza ścieżka) należy przygotować następujące wykresy:
  - wykresy typ1 (osobne wykresy dla każdej reprezentacji grafu) - w formie linii (połączonych punktów),  
    których parametrem jest gęstość grafu i typ algorytmu (Kruskal/Prim lub Dijsktra/Bellman) - czyli 4x2=8 linii na rysunek,
  - wykresy typ2 (osobne wykresy dla każdej gęstości grafu) – w formie linii których parametrem jest typ algorytmu i
    typ reprezentacji grafu (czyli 4 linie na każdy rysunek). c.analogicznie jest dla algorytmu maksymalnego przepływu.
- wszystkie wykresy należy przedstawić w następującym układzie współrzędnych: czas wykonania danego algorytmu (oś Y) w funkcji
- liczby wierzchołków grafu (oś X) – osie należy odpowiednio opisać i koniecznie podać jednostki (dotyczy to głównie zmierzonego czasu),
- wnioski dotyczące efektywności poszczególnych struktur. Wskazać (jeśli są) przyczyny rozbieżności pomiędzy złożonościami teoretycznymi a uzyskanymi eksperymentalnie,
- załączony kod źródłowy w formie elektronicznej (cały projekt wraz z wersją skompilowaną programu) oraz sprawozdanie w formie elektronicznej.

## Ocena projektu

- 3.0 – po jednym algorytmie z każdego problemu (możliwość wykorzystania biblioteki STL)
- 4.0 – po dwa algorytmy z każdego problemu (możliwość wykorzystania biblioteki STL, wersja obiektowa),
- 5.0 – pod dwa algorytmy z każdego problemu (bez korzystania z bibliotek np. STL, wersja obiektowa),
- 5.5 – pod dwa algorytmy z każdego problemu (bez korzystania z bibliotek np. STL, wersja obiektowa), dodatkowo algorytm wyznaczania maksymalnego przepływu Forda-Fulkersona (określanie ście-żek metodą przeszukiwania grafu w głąb i wszerz).
