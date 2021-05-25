#include <iostream>
#include <climits>
#include "FordFulkerson.h"

using std::cout;
using std::cin;



//---------------------
// Metody obiektu queue
//---------------------


queue::queue() {
    this->head = nullptr;
    this->tail = nullptr;
}


// Destruktor - usuwa listę z pamięci
//-----------------------------------
queue::~queue() {
    while (head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void) {
    return !head;
}

// Zwraca początek kolejki.
// Wartość specjalna to -MAXINT
//-----------------------------
int queue::front(void) {
    if (head) return head->data;
    else return -INT_MAX;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int v) {
    slistEl *p = new slistEl;
    p->next = nullptr;
    p->data = v;
    if (tail) tail->next = p;
    else head = p;
    tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void) {
    if (head) {
        slistEl *p = head;
        head = head->next;
        if (!head) tail = NULL;
        delete p;
    }
}


void FordFulkerson::ffMatrix() {
    queue Q;   // Kolejka
    int **C;  // Macierz przepustowości
    int **F;  // Macierz przepływów netto
    int *P;   // Tablica poprzedników
    int *CFP; // Tablica przepustowości rezydualnych
    int n, m, s, t, fmax, cp, x, y, i, j; // Zmienne proste algorytmu
    bool esc;  // Do wychodzenia z zagnieżdżonych pętli

    // Ze standardowego wejścia odczytujemy
    // n - liczbę wierzchołków w grafie sieci
    // m - liczbę krawędzi

    cin >> n >> m;

    // Tworzymy dynamicznie macierze:
    // C - przepustowości krawędzi
    // F - przepływy w krawędziach

    C = new int *[n];
    F = new int *[n];
    for (i = 0; i < n; i++) {
        C[i] = new int[n];
        F[i] = new int[n];
    }

    // Tworzymy dynamicznie tablice:
    // P   - poprzedniki na ścieżkach tworzonych przez BFS
    // CFP - przepustowość ścieżek

    P = new int[n];
    CFP = new int[n];

    // Zerujemy macierze przepustowości i przepływów

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) C[i][j] = F[i][j] = 0;

    // Ze standardowego wejścia odczytujemy definicje krawędzi.
    // Każda definicja składa się z trzech liczb
    // x, y - wierzchołki grafu połączone krawędzią
    // cp  - przepustowość krawędzi
    // Odczytane dane zapamiętujemy: C [ x ][ y ] = cp

    for (i = 0; i < m; i++) {
        cin >> x >> y >> cp;
        C[x][y] = cp;
    }

    // Na koniec odczytujemy numer wierzchołka źródła s
    // oraz numer wierzchołka ujścia t

    cin >> s >> t;

    //**************************************************
    //** Tutaj rozpoczyna się algorytm Edmondsa-Karpa **
    //**************************************************

    // Rozpoczynamy od maksymalnego przepływu równego zero

    fmax = 0;

    // W pętli szukamy ścieżek rozszerzających dotąd,
    // dopóki istnieją w sieci rezydualnej. Każda znaleziona
    // ścieżka zwiększa przepływ wzdłuż zawartych w niej
    // krawędzi grafu sieci przepływowej

    while (true) {

        // Na początku pętli zerujemy tablicę poprzedników P

        for (i = 0; i < n; i++) P[i] = -1;

        // źródło nie posiada poprzednika. Wpisujemy tutaj -2,
        // aby BFS nie wybierało źródła

        P[s] = -2;

        // Do CFP [ s ] wpisujemy największą liczbę całkowitą

        CFP[s] = INT_MAX;

        // Zerujemy kolejkę i umieszczamy w niej źródło s

        while (!Q.empty()) Q.pop();
        Q.push(s);

        // Zmienna esc umożliwia odpowiednie wychodzenie z
        // dwóch zagnieżdżonych pętli - zamiast polecenie goto.

        esc = false;

        // Rozpoczynamy pętlę wyszukującą ścieżki BFS. Pętla kończy
        // się w przypadku braku dalszych wierzchołków w kolejce

        while (!Q.empty()) {

            // Z początku kolejki pobieramy element i usuwamy go z kolejki

            x = Q.front();
            Q.pop();

            // Sprawdzamy wszystkich sąsiadów wierzchołka x przeglądając
            // wiersz macierzy C

            for (y = 0; y < n; y++) {

                // Dla sąsiada y wyznaczamy przepustowość rezydualną
                // krawędzi x->y. Jeśli krawędź nie istnieje w sieci,
                // to otrzymamy w cp wynik zero

                cp = C[x][y] - F[x][y];

                // Sprawdzamy, czy krawędź istnieje oraz czy wierzchołek
                // y nie był już wcześniej wybrany przez BFS. W takim
                // przypadku P [ y ] ma wartość różną od -1.

                if (cp && (P[y] == -1)) {

                    // W P [ y ] zapamiętujemy, iż poprzednikiem y jest x

                    P[y] = x;

                    // Dla wierzchołka y obliczamy dotychczasową przepustowość
                    // rezydualną ścieżki. Jest to mniejsza wartość z przepustowości
                    // ścieżki dla poprzednika x i bieżącej przepustowości
                    // rezydualnej krawędzi x->y.

                    CFP[y] = CFP[x] > cp ? cp : CFP[x];

                    // Jeśli osiągnęliśmy ujście, to ścieżka jest kompletna

                    if (y == t) {

                        // Zwiększamy przepływ maksymalny o przepustowość rezydualną
                        // ścieżki - wykorzystujemy tablicę CFP

                        fmax += CFP[t];

                        // Idziemy wstecz po ścieżce zwiększając przepływy
                        // wzdłuż jej krawędzi w kierunku zgodnym ze ścieżką
                        // oraz zmniejszając przepływy w kierunku przeciwnym

                        i = y;
                        while (i != s) {
                            x = P[i];
                            F[x][i] += CFP[t];
                            F[i][x] -= CFP[t];
                            i = x;
                        }

                        // Ustawiamy esc na true, co spowoduje wyjście z obu pętli

                        esc = true;
                        break;
                    }

                    // Jeśli wierzchołek y nie jest ujściem t, to dopisujemy
                    // go na końcu kolejki Q i kontynuujemy pętlę BFS

                    Q.push(y);
                }
            }

            // Tutaj wychodzimy z pętli while, jeśli
            // została znaleziona ścieżka rozszerzająca

            if (esc) break;
        }

        // Jeśli nie znaleziono ścieżki rozszerzającej, to esc = false
        // i w tym miejscu nastąpi wyjście z głównej pętli while

        if (!esc) break;
    }

    // Prezentujemy wyniki obliczeń. Najpierw wypisujemy
    // wartość maksymalnego przepływu

    cout << "\n" << "fmax = " << fmax << "\n\n";

    // Następnie wypisujemy przepływy netto wzdłuż krawędzi

    for (x = 0; x < n; x++)
        for (y = 0; y < n; y++)
            if (C[x][y]) cout << x << " -> " << y << " " << F[x][y] << ":" << C[x][y] << "\n";

    cout << "\n";

    // Usuwamy zmienne dynamiczne

    for (i = 0; i < n; i++) {
        delete[] C[i];
        delete[] F[i];
    }

    delete[] C;
    delete[] F;
    delete[] P;
    delete[] CFP;
}

//void FordFulkerson::display(int maxFlow, int vertices) {
//    cout << "\n" << "fmax = " << maxFlow << "\n\n";
//
//    for (int x = 0; x < vertices; x++)
//        for (int y = 0; y < vertices; y++)
//            if (sasiedzi[x][y])
//                cout << "(" << x << "," << y << ")" << " " << ": " << sasiedzi[x][y] << "|" << sasiedzi2[x][y] << "\n";
//
//    cout << "\n";
//}



