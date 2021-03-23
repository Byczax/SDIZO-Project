#include <iostream>

#include "double_list.h"

using namespace std;

void myArray() {
    cout << "W implementacji";
}

void doubleList() {
    cout << "W implementacji";
    MyList myList;
    bool exit = false;
    int input;
    int value;
    unsigned int index;
    while (!exit) {
        cout << "0. Wyjście \n"
                "1. Dodaj element z przodu \n"
                "2. Dodaj element z tyłu \n"
                "3. Dodaj element gdziekolwiek \n"
                "4. Usuń element z przodu \n"
                "5. Usuń element z tyłu \n"
                "6. Usuń element gdziekolwiek \n"
                "7. Usuń wartość (jeżeli istnieje) \n"
                "8. Znajdź element \n";
        cin >> input;
        switch (input) {
            case 0:
                exit = true;
                break;
            case 1:
                cin >> value;
                myList.addElementFront(value);
                break;
            case 2:
                cin >> value;
                myList.addElementBack(value);
                break;
            case 3:
                cin >> value;
                cin >> index;
                myList.addElementAnywhere(value, index);
                break;
            case 4:
                myList.removeElementFront();
                break;
            case 5:
                cin >> value;
                myList.removeElementBack();
                break;
            case 6:
                cin >> index;
                myList.removeElementAnywhere(index);
                break;
            case 7:
                cin >> value;
                myList.removeValue(value);
                break;
            case 8:
                cin >> value;
                myList.findValue(value);
                break;
            default:
                cout << "Błąd, zły wybór";
                break;
        }
    }
}

void heap() {
    cout << "W implementacji";
}

void tree() {
    cout << "W implementacji";
}

int main() {
    bool exit = false;
    int input;
    while (!exit) {
        cout << "0. Wyjście \n"
                "1. Tablica \n"
                "2. Lista Dwukierunkowa \n"
                "3. Kopiec Binarny \n"
                "4. Drzewo Czerwono-czarne \n";
        cin >> input;
        switch (input) {
            case 0:
                exit = true;
                break;
            case 1:
                myArray();
                break;
            case 2:
                doubleList();
                break;
            case 3:
                heap();
                break;
            case 4:
                tree();
                break;
            default:
                cout << "Błąd, zły wybór";
                break;
        }
    }
}