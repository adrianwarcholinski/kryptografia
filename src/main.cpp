#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

void wyswietlNaglowek() {
    cout << "Algorytm szyfrowania AES." << endl
         << "Autorzy:" << endl
         << "Aleksandra Ruta" << endl
         << "Adrian Warcholinski" << endl
         << "Kamil Piatkowski" << endl;
}


//
//void wczytajDane(string &tresc, string &klucz) {
//    short wybor;
//    string tekst="";
//    cout << "Podaj metode wprowadzania danych:" << endl
//         << "[1] Tekst wprowadzony z klawiatury" << endl
//         << "[2] Tekst wczytywany z pliku" << endl
//         << "Wybierz opcje: ";
//    while(true) {
//        cin >> wybor;
//        cin.ignore();
//        if((wybor == 1) || (wybor == 2)) {
//            break;
//        } else {
//            cout << "Nieprawidlowa opcja. Wybierz opcje: ";
//        }
//    }
//    if(wybor == 1) {
//        cout << "Wprowadz tekst:";
//        getline(cin, tekst);
//        tresc = tekst;
//        cout << "Wpisz max 16-znakowy klucz:";
//        while (true) {
//            getline(cin, klucz);
//            if (klucz.length() <= 16) {
//                break;
//            } else {
//                cout << "Niepoprawny klucz - wpisz poprawny max 16-znakowy klucz: ";
//            }
//        }
//        for (int i = klucz.length(); i < 16; i++) {
//            klucz += (char) 0;
//        }
//    }
//    else if(wybor == 2) {
//        fstream plik;
//        plik.open("../dane.txt", ios::in );
//        if( plik.good() ) {
//            getline(plik, tresc);
//            getline(plik, klucz);
//            plik.close();
//        } else cout << "Blad - nie udalo sie otworzyc pliku" << endl;
//    }
//}


int main() {
    wyswietlNaglowek();

    return 0;
}