#include "Prim.h"

#include <iostream>

#include <string>

#define    MX 10000 //bardzo duza liczba potrzebna	do wag

using namespace std;

void Prim::Prim() {
    int graf[100][100]; // graf nad	ktorym bedziemy	pracowac
    int odwiedzone[MX]; //tablica odwiedzonych
    int waga[MX];        //tablica wag poszczegolnych polaczen
    int nastepnik[MX];  // tablica nastepnych polaczen

    int n, m;        //n	- liczba wierzkochlkow	 m - liczba krawedzi
    int g;            //liczba przypadk�w	testowych
    int a, b, c;        // dane wejsciowe a- pierwszy wierzcholek, b- drugi	wierzcholek, c - waga
    int wiersz, wierzcholki, koszt, i;

    cout << "Podaj liczbe przypadkow\n";
    cin >> g; //pobieranie ilosci przypadkow

    for (int z = 0; z < g; z++)    // glowna petla	programu
    {

        printf("Podaj liczbe wierzcholkow i krawedzi\n");
        cin >> n >> m; //pobieranie n(liczba	wierzcholkow) i	m(liczba krawedzi)

        for (int e = 0; e < n; e++) //inicjalizacja danych
        {
            nastepnik[e] = odwiedzone[e] = 0; //nie ma poprzednikow i nastepnikow
            waga[e] = MX; // waga jest rowna max
            for (int r = 0; r < n; r++) {
                graf[e][r] = 0; // wypelnianie tablicy zerami
            }
        }

        for (int q = 0; q < m; q++) //pobieranie	drog w grafie
        {
            printf("Podaj wierzcholki krawedzi i jej wage\n");
            cin >> a >> b >> c; //droga miedzy	a i b o	wadze c
            graf[a][b] = graf[b][a] = c; //wypelnianie tablicy danymi uzytkownika
        }

        // inicjalizacja danych	do algorytmu Prima
        wiersz = 1; //zaczynamy od pierwszego wiersza, czyli przeszukujemy wszystkie polaczenia pierwszego wierzcholka
        waga[wiersz] = 0;    // pierwsza waga rowna jest zero
        wierzcholki = 1; //zaczynamy od pierwszech wierzcholka
        odwiedzone[wiersz] = 1; // pierwszy wierzcholek odwiedzilismy, bo	zaczynamy od niego

        //algorytm Prima
        while (wierzcholki != n)  // n liczba wierzcholkow
        {
            for (i = 0; i < n; i++)//przeszukanie pierwszego wiersza
            {
                if (graf[wiersz][i] != 0)//jezeli nie ma polaczenia z wierzcholkien to nie	wchodz
                {
                    if (odwiedzone[i] == 0)// jezeli byl odiweczony to	nie wchodz
                    {
                        if (waga[i] > graf[wiersz][i])// jezeli jest droga	o mniejszym koszcie to nie wchodz
                        {
                            waga[i] = graf[wiersz][i]; // znaleziono najtansza droge,	podmiana za wczesniejsza
                        }
                    }
                }
            }

            koszt = MX; // maksymalny	koszt
            for (i = 0; i < n; i++) // zanotowanie	wagi w tabilcy
            {
                if (odwiedzone[i] == 0) //	sprawdzenie czy	byl odwiedzony
                {
                    if (waga[i] < koszt) // sprawdzenie czy waga jest nizsza od maxa
                    {
                        koszt = waga[i]; // ustawienie nowej wagi	 jako koszt
                        wiersz = i; // ustawienie	wiersza	w ktorym zmienilem wage
                    }
                }
            }

            odwiedzone[wiersz] = 1; // odwiedzony wierzcholek
            wierzcholki++; // przechodzimy do nstepnego wierzcholka
        }

        koszt = 0; //koszty na poczatku rowne zero
        for (i = 0; i < n; i++) // dodaje wagi
        {
            koszt += waga[i];    //suma wag
        }
        cout << koszt << "\n"; //wypisanie an ekran
    }
}
