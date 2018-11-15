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
    macierze = new unsigned char **[liczbaMacierzyStanu];
    for (int i(0); i < liczbaMacierzyStanu; ++i) {
        macierze[i] = new unsigned char *[4];
        for (int j(0); j < 4; ++j) {
            macierze[i][j] = new unsigned char[4];
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

void Macierze::mixColumns() {
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int k = 0; k < 4; k++) {
            unsigned char a[4];
            unsigned char b[4];
            unsigned char h;
            for (int c = 0; c < 4; c++) {
                a[c] = macierze[i][c][k];
                h = (unsigned char)((signed char)macierze[i][c][k] >> 7);
                b[c] =macierze[i][c][k] << 1;
                b[c] ^= 0x1B & h;
            }
            macierze[i][0][k]  = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
            macierze[i][1][k]  = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
            macierze[i][2][k]  = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
            macierze[i][3][k]  = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
        }
   }
}

void Macierze::inverseShiftRows() {
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
                for (int b = 2; b >= 0; b--) {
                    swap(macierze[i][j][b], macierze[i][j][b + 1]);
                }
            }
        }
    }
}

void Macierze::inverseSubstituteBytes() {
    SBox* sbox=new SBox();
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                macierze[i][j][k]=sbox->nowyBajtOdwrocony(macierze[i][j][k]);
            }
        }
    }
    delete sbox;
}

void Macierze::inverseMixColumns() {
 
}


