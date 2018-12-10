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
string stringToIntString(string tresc){
    stringstream bufor;
    for(int i=0; i<tresc.size();i++){
        bufor<< setfill('0') << setw(3) << int(tresc[i]);
    }
    return bufor.str();
}

string intStringToString(string tresc){
    string wynik;
    for(int i=0; i<tresc.size();i+=3){
        stringstream bufor;
        for(int k=i;k<i+3;k++) {
            bufor<<tresc[k];
        }
        wynik+=char(stoi(bufor.str(), nullptr,8));
    }
    return wynik;
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
    string szyfrowanaLiczbaString=wczytajDane();
    BigInt szyfrowanaLiczba(szyfrowanaLiczbaString);
    cout << "Wykonuje test pierwszosci..." << endl;
    BigInt p(257);
    bool isPrime = Math::isPrime(p);
    if(isPrime) {
        cout << "Liczba p przeszla test pierwszosci Fermata." << endl;
        BigInt a("70");
        BigInt g("15");
        BigInt b = Math::fastPower(g, p, a);
        cout << "b = " << b << endl;
        BigInt k("127");
        cout << "a = " << a << endl;
        cout << "g = " << g << endl;
        cout << "b = " << b << endl;
        cout << "k = " << k << endl;
        cout << "p = " << p << endl;

        cout << "Wyznaczam C1 i C2..." << endl;
        BigInt c1 = Math::fastPower(g, p, k);

        cout << "Szyfrowana liczba: " << szyfrowanaLiczba << endl;
        BigInt c2 = (szyfrowanaLiczba * Math::fastPower(b, k)) % p;

        cout << "Kryptogram: " << endl;
        cout << "C1: " << c1 << endl;
        cout << "C2: " << c2 << endl;

        cout << "Deszyfrowanie... " << endl;
        BigInt exponent = a*(p-2);
        BigInt d = (c2 * Math::fastPower(c1, exponent)) % p;

        cout << "Tekst jawny: " << endl;
        cout << d << endl;
    } else {
        cout << "Liczba nie przeszla testu pierwszosci Fermata." << endl;
    }
    return 0;
}