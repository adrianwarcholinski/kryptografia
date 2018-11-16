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
    macierze[0][0][0]=142;
    macierze[0][1][0]=77;
    macierze[0][2][0]=161;
    macierze[0][3][0]=188;
    macierze[0][0][1]=159;
    macierze[0][1][1]=220;
    macierze[0][2][1]=88;
    macierze[0][3][1]=157;
}

void Macierze::wyswietlMacierze() {
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                cout <<dec<< (int)macierze[i][j][k] << " ";
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

char GMul(char a, char b) { // Galois Field (256) Multiplication of two Bytes
    char p = 0;

    for (int counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) {
            p ^= a;
        }

        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }
    return p;
}

void Macierze::mixColumns() {
    unsigned char bufor[4];
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
            for (int k = 0; k < 4; k++) { // s[0,c]
                bufor[0] = (unsigned char)(GMul(0x02, macierze[i][0][k]) ^ GMul(0x03, macierze[i][1][k]) ^ macierze[i][2][k] ^ macierze[i][3][k]);
                bufor[1] = (unsigned char)(macierze[i][0][k] ^ GMul(0x02, macierze[i][1][k]) ^ GMul(0x03, macierze[i][2][k]) ^ macierze[i][3][k]);
                bufor[2] = (unsigned char)(macierze[i][0][k] ^ macierze[i][1][k] ^ GMul(0x02, macierze[i][2][k]) ^ GMul(0x03, macierze[i][3][k]));
                bufor[3] = (unsigned char)(GMul(0x03, macierze[i][0][k]) ^ macierze[i][1][k] ^ macierze[i][2][k] ^ GMul(0x02, macierze[i][3][k]));
                for(int b=0;b<4;b++){
                    macierze[i][b][k]=bufor[b];
                }
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
    unsigned char bufor[4];
    for (int i = 0; i < liczbaMacierzyStanu; i++) {
        for (int k = 0; k < 4; k++) { // s[0,c]
            bufor[0] = (unsigned char)(GMul(14, macierze[i][0][k]) ^ GMul(11, macierze[i][1][k]) ^ GMul(13, macierze[i][2][k]) ^ GMul(9, macierze[i][3][k]));
            bufor[1] = (unsigned char)(GMul(9, macierze[i][0][k]) ^ GMul(14, macierze[i][1][k]) ^ GMul(11, macierze[i][2][k]) ^ GMul(13, macierze[i][3][k]));
            bufor[2] = (unsigned char)(GMul(13, macierze[i][0][k]) ^ GMul(9, macierze[i][1][k]) ^ GMul(14, macierze[i][2][k]) ^ GMul(11, macierze[i][3][k]));
            bufor[3] = (unsigned char)(GMul(11, macierze[i][0][k]) ^ GMul(13, macierze[i][1][k]) ^ GMul(9, macierze[i][2][k]) ^ GMul(14, macierze[i][3][k]));
            for(int b=0;b<4;b++){
                macierze[i][b][k]=bufor[b];
            }
        }
    }
}


