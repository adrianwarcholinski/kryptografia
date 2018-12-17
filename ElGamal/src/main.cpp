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
    DuzyInt p("32553564085451391275856713123390311890318450590292519057317422150292415523109201659612228535643301240109780758567295324228515924941497212721749572274659477550597202013381665366413595298117580519523680536179884679717727570822180352036496257141711892987237470619766362793748626538831203668035059415389014240677");
    bool isPrime = Math::isPrime(p);
    if(isPrime) {
        cout << "Liczba p przeszla test pierwszosci Fermata." << endl;
        DuzyInt a = p - 12465;
        DuzyInt g = p - 134649796;
        DuzyInt h = Math::fastPower(g, p, a);
        DuzyInt r = p - 1214644;
        cout << "a = " << a << endl;
        cout << "g = " << g << endl;
        cout << "h = " << h << endl;
        cout << "r = " << r << endl;
        cout << "p = " << p << endl;
        cout << "Wyznaczam C1 i C2..." << endl;
        DuzyInt c1 = Math::fastPower(g, p, r);

        cout << "Szyfrowany tekst: " << szyfrowanyTekst << endl;
        DuzyInt c2[szyfrowanyTekst.size()];
        for(int i=0;i<szyfrowanyTekst.size();i++){
            c2[i]= (szyfrowaneLiczby[i] * Math::fastPower(h, r)) % p;
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