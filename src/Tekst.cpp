//
// Created by adria on 12.10.2018.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <Tekst.h>

#include "Tekst.h"
#include "SBox.h"

void Tekst::replaceTresc() {
    string tempStr = "";
    for(int i=0; i<macierze->liczbaMacierzyStanu; i++) {
        for(int w=0; w<4; w++) {
            for(int k=0; k<4; k++) {
                tempStr += macierze->macierze[i][w][k];
            }
        }
    }
    tresc = tempStr;
}

Tekst::Tekst(string kluczPodstawowy, string tresc) {
    this->tresc = tresc;
    this->kluczPodstawowy = kluczPodstawowy;
    this->macierze = new Macierze(tresc);
    rozszerzKlucz();
}

Tekst::~Tekst() {
    delete macierze;
}

unsigned int potega(unsigned int podstawa, unsigned int wykladnik) {
    unsigned int wynik = 1;
    for(int i=1; i<=wykladnik; i++) {
        wynik *= podstawa;
    }
    return wynik;
}

void Tekst::rozszerzKlucz() {
    SBox* sbox = new SBox();
    this->kluczRozszerzony = kluczPodstawowy;

    for(int a=0; a<10; a++) {
        vector<unsigned char> tempVector(4);
        for(int i=0; i<tempVector.size(); i++) {
            tempVector[i] = kluczRozszerzony[kluczRozszerzony.length()-4+i];
        }

        for(int i=0; i<tempVector.size()-1; i++) {
            swap(tempVector[i],tempVector[i+1]);
        }

        for(int i=0; i<tempVector.size(); i++) {
            tempVector[i] = sbox->nowyBajtNormalny(tempVector[i]);
        }

        tempVector[0] = tempVector[0] ^ potega(2, a);

        vector<unsigned char> tempVector2(4);

        for(int i=0; i<tempVector2.size(); i++) {
            tempVector2[i] = kluczRozszerzony[kluczRozszerzony.length()-16+i];
        }

        for(int i=0; i<tempVector2.size(); i++) {
            tempVector[i] ^= tempVector2[i];
        }

        for(int i=0; i<tempVector2.size(); i++) {
            kluczRozszerzony += tempVector[i];
        }
        vector<unsigned char> tempVector3(4);
        vector<unsigned char> tempVector4(4);

        for(int i=0; i<3; i++) {
            for(int j=0; j<tempVector3.size(); j++) {
                tempVector3[j] = kluczRozszerzony[kluczRozszerzony.length()-4+j];
            }
            for(int j=0; j<tempVector4.size(); j++) {
                tempVector4[j] = kluczRozszerzony[kluczRozszerzony.length()-16+j];
            }
            for(int j=0; j<tempVector4.size(); j++) {
                tempVector3[j] ^= tempVector4[j];
            }
            for(int j=0; j<tempVector3.size(); j++) {
                kluczRozszerzony += tempVector3[j];
            }
        }
    }
    delete sbox;
}

void Tekst::addRoundKey(int round) {
    string roundKey = kluczRozszerzony.substr(round*16, 16);
    for(int i=0; i<macierze->liczbaMacierzyStanu; i++) {
        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                macierze->macierze[i][j][k] ^= roundKey.at(j*4+k);
            }
        }
    }
    replaceTresc();
}

