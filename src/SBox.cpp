//
// Created by adria on 26.10.2018.
//

#include "SBox.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

SBox::SBox() {
    this->tabelaNormalna = new unsigned char*[16];
    this->tabelaOdwrocona = new unsigned char*[16];
    for(int i=0; i<16; i++) {
        this->tabelaNormalna[i] = new unsigned char[16];
        this->tabelaOdwrocona[i] = new unsigned char[16];
    }
    wczytajSBox();
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
                this->tabelaNormalna[i][j] = bufor;
                plikOdwrocony >> hex >> bufor;
                plikOdwrocony.ignore(1);
                this->tabelaOdwrocona[i][j] = bufor;
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
            cout << setw(2) << hex << (unsigned int)this->tabelaNormalna[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl << "SBox odwrocony: " << endl;
    for(int i=0; i<16; i++) {
        for(int j=0; j<16; j++) {
            cout << setw(2) << (unsigned int)this->tabelaOdwrocona[i][j] << ", ";
        }
        cout << endl;
    }
}

unsigned char SBox::nowyBajtNormalny(unsigned char bajt) {
    unsigned char kopiaBajt = bajt;
    bajt >>= 4; // zostaje wiodaca czesc bajtu
    int wiersz = bajt;
    kopiaBajt <<= 4;
    kopiaBajt >>= 4;
    int kolumna = kopiaBajt;
    return this->tabelaNormalna[wiersz][kolumna];
}

unsigned char SBox::nowyBajtOdwrocony(unsigned char bajt) {
    unsigned char kopiaBajt = bajt;
    bajt >>= 4; // zostaje wiodaca czesc bajtu
    int wiersz = bajt;
    cout << "wiersz: " << wiersz;
    kopiaBajt <<=4;
    kopiaBajt >>= 4;
    int kolumna = kopiaBajt;
    cout << "kolumna: " << kolumna;
    return this->tabelaOdwrocona[wiersz][kolumna];
}
