#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "TekstJawny.h"

using namespace std;

void wyswietlNaglowek() {
    cout << "Algorytm szyfrowania AES." << endl
         << "Autorzy:" << endl
         << "Aleksandra Ruta" << endl
         << "Adrian Warcholinski" << endl
         << "Kamil Piatkowski" << endl;
}

// Zrobione w stringu, aby nie przejmowac sie dlugoscia ciagu wejsciowego - Adrian
string wczytajTekst() {
    short wybor;
    string tekst;
    cout << "Podaj metode wprowadzania danych:" << endl
         << "[1] Tekst wprowadzony z klawiatury" << endl
         << "[2] Tekst wczytywany z pliku" << endl
         << "Wybierz opcje: ";
    while(true) {
        cin >> wybor;
        if((wybor == 1) || (wybor == 2)) {
            break;
        } else {
            cout << "Nieprawidlowa opcja. Wybierz opcje: ";
        }
    }
    if(wybor == 1) {
        cout << "Wprowadz tekst:" << endl;
        cin >> tekst;
        return tekst;
    }
}

int main() {
    wyswietlNaglowek();
    TekstJawny tekstJawny(wczytajTekst());
    return 0;
}