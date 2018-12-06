#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <bitset>
#include "../include/BigInt.h"
#include "../include/Math.h"
using namespace std;

void wyswietlNaglowek() {
    cout << "Algorytm szyfrowania AES." << endl
         << "Autorzy:" << endl
         << "Aleksandra Ruta" << endl
         << "Adrian Warcholinski" << endl
         << "Kamil Piatkowski" << endl;
}

void wczytajDane(string &tresc) {
    short wybor;
    string tekst="";
    cout << "Podaj metode wprowadzania danych:" << endl
         << "[1] Tekst wprowadzony z klawiatury" << endl
         << "[2] Tekst wczytywany z pliku" << endl
         << "Wybierz opcje: ";
    while(true) {
        cin >> wybor;
        cin.ignore();
        if((wybor == 1) || (wybor == 2)) {
            break;
        } else {
            cout << "Nieprawidlowa opcja. Wybierz opcje: ";
        }
    }
    if(wybor == 1) {
        cout << "Wprowadz tekst:";
        getline(cin, tekst);
        tresc = tekst;
    }
    else if(wybor == 2) {
        fstream plik;
        plik.open("../dane.txt", ios::in );
        if( plik.good() ) {
            getline(plik, tresc);
            plik.close();
        } else cout << "Blad - nie udalo sie otworzyc pliku dane.txt" << endl;
    }
}


int main() {
    wyswietlNaglowek();
    string tekst;
    //wczytajDane(tekst);
    return 0;
}