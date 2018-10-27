#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "TekstJawny.h"
#include "SBox.h"

using namespace std;

void wyswietlNaglowek() {
    cout << "Algorytm szyfrowania AES." << endl
         << "Autorzy:" << endl
         << "Aleksandra Ruta" << endl
         << "Adrian Warcholinski" << endl
         << "Kamil Piatkowski" << endl;
}

string wczytajTekst() {
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
        cin.ignore();
        getline(cin, tekst);
    }
    else if(wybor == 2) {
        cout << "Nazwa pliku: dane.txt" << endl;
        fstream plik;
        string linia;
        plik.open( "../dane.txt", ios::in );
        if( plik.good() ) {
            while( !plik.eof() ) {
                getline(plik, linia);
                tekst.append(linia+'\n');
            }
            plik.close();
        } else cout << "Blad - nie udalo sie otworzyc pliku" << endl;
    }
    return tekst;
}
string wczytajKlucz(){
    string klucz="";
    cout << "Wpisz max 16-znakowy klucz:";
    while(true) {
        getline(cin, klucz);
        if(klucz.length() <= 16) {
            break;
        } else {
            cout << "Niepoprawny klucz - wpisz poprawny max 16-znakowy klucz: ";
        }
    }
    for(int i = klucz.length(); i<16; i++) {
        klucz += (char)0;
    }
    return klucz;
}

int main() {
    wyswietlNaglowek();
    SBox* sbox = new SBox();

    //sbox->wyswietlSBoxy();

    TekstJawny tekstJawny(wczytajKlucz(),wczytajTekst());
    //tekstJawny.macierze->wyswietlMacierze();

    cin.get(); // na potrzeby uruchamiania z wiersza polecen
    return 0;
}