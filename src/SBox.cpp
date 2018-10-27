//
// Created by adria on 26.10.2018.
//

#include "SBox.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

SBox::SBox() {
    tabelaNormalna = new char*[16];
    tabelaOdwrocona = new char*[16];
    for(int i=0; i<16; i++) {
        tabelaNormalna[i] = new char[16];
        tabelaOdwrocona[i] = new char[16];
    }
    wczytajSBox();
}

SBox::~SBox() {
//    char** tabelaNormalna;
//    char** tabelaOdwrocona;
    for(int i=0; i<16; i++) {
        delete[] tabelaNormalna[i];
        delete[] tabelaOdwrocona[i];
    }
    delete[] tabelaNormalna;
    delete[] tabelaOdwrocona;
}

void SBox::wczytajSBox() {
    fstream plikNormalny;
    fstream plikOdwrocony;
    int bufor = 0;
    plikNormalny.open("../S-BOX.txt", ios::in);
    plikOdwrocony.open("../S-BOX-inversed.txt", ios::in);
    if(plikNormalny.good() && plikOdwrocony.good()) {
        for(int i=0; i<16; i++) {
            for(int j=0; j<16; j++) {
                plikNormalny >> hex >> bufor;
                plikNormalny.ignore(1);
                tabelaNormalna[i][j] = bufor;
                plikOdwrocony >> hex >> bufor;
                plikOdwrocony.ignore(1);
                tabelaOdwrocona[i][j] = bufor;
            }
        }
        plikNormalny.close();
        plikOdwrocony.close();
    } else {
        cout << "Blad przy wczytywaniu plikow S-BOX.txt oraz S-BOX-inverted.txt" << endl;
    }
}

void SBox::wyswietlSBoxy() {
    cout << "SBox normalny: " << endl;
    for(int i=0; i<16; i++) {
        for(int j=0; j<16; j++) {
            cout << setw(2) << hex << (int)tabelaNormalna[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl << "SBox odwrocony: " << endl;
    for(int i=0; i<16; i++) {
        for(int j=0; j<16; j++) {
            cout << setw(2) << hex << (int)tabelaOdwrocona[i][j] << ", ";
        }
        cout << endl;
    }
}

char SBox::nowyBajtNormalny(char bajt) {
    unsigned char kopiaBajt = bajt;
    bajt >>= 4; // zostaje wiodaca czesc bajtu
    int wiersz = bajt;
    kopiaBajt <<= 4;
    kopiaBajt >>= 4;
    int kolumna = kopiaBajt;
    return tabelaNormalna[wiersz][kolumna];
}

char SBox::nowyBajtOdwrocony(char bajt) {
    char kopiaBajt = bajt;
    bajt >>= 4; // zostaje wiodaca czesc bajtu
    int wiersz = bajt;
    cout << "wiersz: " << wiersz;
    kopiaBajt <<=4;
    kopiaBajt >>= 4;
    int kolumna = kopiaBajt;
    cout << "kolumna: " << kolumna;
    return tabelaOdwrocona[wiersz][kolumna];
}
