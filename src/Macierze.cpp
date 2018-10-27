//
// Created by adria on 26.10.2018.
//

#include "../include/Macierze.h"
#include <string>
#include <cmath>
#include <iostream>
#include <Macierze.h>
#include <SBox.h>


using namespace std;

Macierze::Macierze(string tresc) {
    utworzMacierze(tresc);
    wypelnijMacierze(tresc);
}

Macierze::~Macierze() {
    usunMacierze();
}

void Macierze::utworzMacierze(string tresc) {
    liczbaMacierzyStanu = int(ceil(tresc.length() * 1.0 / 16));
    macierze = new char **[liczbaMacierzyStanu];
    for (int i(0); i < liczbaMacierzyStanu; ++i) {
        macierze[i] = new char *[4];
        for (int j(0); j < 4; ++j) {
            macierze[i][j] = new char[4];
        }
    }
}

void Macierze::wypelnijMacierze(string tresc) {
    int licznik = 0;
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
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
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                cout << macierze[i][j][k];
            }
            cout << endl;
        }
        cout << endl;
    }
}
void Macierze::usunMacierze(){
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            delete[] macierze[i][j];
        }
        delete[] macierze[i];
    }
    delete[] macierze;
}

void Macierze::shiftRows() {
    int i;
    if(liczbaMacierzyStanu-3<0){
        i=0;
    }
    else{
        i=liczbaMacierzyStanu-3;
    }
    for(;i<liczbaMacierzyStanu;i++){
        for(int j=1;j<4;j++){
            for(int a=0;a<j;a++) {
                for (int b = 0; b < 3; b++) {
                    swap(macierze[i][j][b], macierze[i][j][b + 1]);
                }
            }
        }
    }
}

void Macierze::substituteBytes() {
    SBox* sbox=new SBox();
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                    macierze[i][j][k]=sbox->nowyBajtNormalny(macierze[i][j][k]);
                }
            }
        }
    delete sbox;
}

void Macierze::mixColumns() {  //zły - wychodzacy poza zakres
    char macierzStala[4][4]={{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}};
    char kolumna[4];
    char bufor;
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                bufor=0;
                for(int a=0;a<4;a++){
                        bufor += macierze[i][a][k] * macierzStala[j][a];
                }
                kolumna[j]=bufor;
            }
            for(int b=0;b<4;b++){
                macierze[i][b][k]=kolumna[b];
            }
        }
   }
}


