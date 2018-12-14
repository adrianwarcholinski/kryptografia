#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <bitset>
#include "DuzyInt.h"
#include "../include/Math.h"
using namespace std;

void wyswietlNaglowek() {
    cout << "Algorytm szyfrowania AES." << endl
         << "Autorzy:" << endl
         << "Aleksandra Ruta" << endl
         << "Adrian Warcholinski" << endl
         << "Kamil Piatkowski" << endl;
}
DuzyInt charToBigInt(char znak){
    DuzyInt wynik;
    wynik=int(znak);
    return wynik;
}

char BigIntToChar(DuzyInt znak){
    return char(stoi(znak.getLiczba()));
}

string wczytajDane() {
    short wybor;
    string tresc;
    string tekst;
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
    return tresc;
}


int main() {
    wyswietlNaglowek();
    string szyfrowanyTekst=wczytajDane();
    DuzyInt szyfrowaneLiczby[szyfrowanyTekst.size()];
    for(int i=0;i<szyfrowanyTekst.size();i++){
        szyfrowaneLiczby[i]=charToBigInt(szyfrowanyTekst[i]);
    }
    DuzyInt szyfrowanaLiczba(szyfrowanyTekst);
    cout << "Wykonuje test pierwszosci..." << endl;
    DuzyInt p(257);
    bool isPrime = Math::isPrime(p);
    if(isPrime) {
        cout << "Liczba p przeszla test pierwszosci Fermata." << endl;
        DuzyInt a("70");
        DuzyInt g("15");
        DuzyInt b = Math::fastPower(g, p, a);
        cout << "b = " << b << endl;
        DuzyInt k("127");
        cout << "a = " << a << endl;
        cout << "g = " << g << endl;
        cout << "b = " << b << endl;
        cout << "k = " << k << endl;
        cout << "p = " << p << endl;

        cout << "Wyznaczam C1 i C2..." << endl;
        DuzyInt c1 = Math::fastPower(g, p, k);

        cout << "Szyfrowany tekst: " << szyfrowanyTekst << endl;
        DuzyInt c2[szyfrowanyTekst.size()];
        for(int i=0;i<szyfrowanyTekst.size();i++){
            c2[i]= (szyfrowaneLiczby[i] * Math::fastPower(b, k)) % p;
        }


        cout << "Kryptogram: " << endl;
        cout << "C1: " << c1 << endl;
        cout << "C2: ";
        for(int i=0;i<szyfrowanyTekst.size();i++){
            cout<<c2[i]<<",";
        }
        cout<<endl;
        cout << "Deszyfrowanie... " << endl;
        DuzyInt exponent = a*(p-2);
        DuzyInt d[szyfrowanyTekst.size()];
        for(int i=0;i<szyfrowanyTekst.size();i++) {
            d[i] = (c2[i] * Math::fastPower(c1, exponent)) % p;
        }
        cout << "Tekst jawny: " << endl;
        for(int i=0;i<szyfrowanyTekst.size();i++) {
            cout << BigIntToChar(d[i]);
        }

    } else {
        cout << "Liczba nie przeszla testu pierwszosci Fermata." << endl;
    }
    return 0;
}