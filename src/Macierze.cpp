//
// Created by adria on 26.10.2018.
//

#include "../include/Macierze.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

Macierze::Macierze(string tresc) {
    utworzMacierze(tresc);
    wypelnijMacierze(tresc);
}

Macierze::~Macierze() {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            delete[] macierze[i][j];
        }
        delete[] macierze[i];
    }
    delete[] macierze;
}

void Macierze::utworzMacierze(string tresc) {
    liczbaMacierzy = int(ceil(tresc.length() * 1.0 / 16));
    macierze = new char **[liczbaMacierzy];
    for (int i(0); i < liczbaMacierzy; ++i) {
        macierze[i] = new char *[4];
        for (int j(0); j < 4; ++j) {
            macierze[i][j] = new char[4];
        }
    }
}

void Macierze::wypelnijMacierze(string tresc) {
    int licznik = 0;
    for (int i = 0; i < liczbaMacierzy; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (tresc.length() <= licznik) {
                    macierze[i][j][k] = 0;
                }
                else {
                    macierze[i][j][k] = tresc[licznik];
                    licznik++;
                }
            }
        }
    }
}

void Macierze::wyswietlMacierze() {
    for (int i = 0; i < liczbaMacierzy; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                cout << macierze[i][j][k];
            }
            cout << endl;
        }
        cout << endl;
    }
}

