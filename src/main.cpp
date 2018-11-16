#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Tekst.h"
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
string wczytajKlucz() {
    string klucz = "";
    cout << "Wpisz max 16-znakowy klucz:";
    while (true) {
        getline(cin, klucz);
        if (klucz.length() <= 16) {
            break;
        } else {
            cout << "Niepoprawny klucz - wpisz poprawny max 16-znakowy klucz: ";
        }
    }
    for (int i = klucz.length(); i < 16; i++) {
        klucz += (char) 0;
    }
    //cout<<"Klucz: "<<klucz<<endl;
    //cout<<"KL"<<klucz.length()<<endl;
    return klucz;
}

void encrypt(Tekst &tekstJawny) {
    tekstJawny.addRoundKey(0);
    for(int i=1; i<=9; i++) {
        tekstJawny.macierze->substituteBytes();
        tekstJawny.macierze->shiftRows();
        tekstJawny.macierze->mixColumns();
        tekstJawny.addRoundKey(i);
    }
    tekstJawny.macierze->substituteBytes();
    tekstJawny.macierze->shiftRows();
    tekstJawny.addRoundKey(10);
}

void decrypt(Tekst &szyfrogram) {
    szyfrogram.addRoundKey(10);
    szyfrogram.macierze->inverseShiftRows();
    szyfrogram.macierze->inverseSubstituteBytes();
    for (int i = 1; i <= 9; i++) {
        szyfrogram.addRoundKey(10 - i);
        szyfrogram.macierze->inverseMixColumns();
        szyfrogram.macierze->inverseShiftRows();
        szyfrogram.macierze->inverseSubstituteBytes();
    }
    szyfrogram.addRoundKey(0);
}

int main() {
    wyswietlNaglowek();
    Tekst tekst(wczytajKlucz(),wczytajTekst());
    tekst.macierze->wyswietlMacierze();
    encrypt(tekst);
    decrypt(tekst);
    tekst.macierze->wyswietlMacierze();

    return 0;
}