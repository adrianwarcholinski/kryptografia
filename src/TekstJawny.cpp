//
// Created by adria on 12.10.2018.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include "TekstJawny.h"
#include "SBox.h"

TekstJawny::TekstJawny(string kluczPodstawowy, string tresc) {
    this->tresc = tresc;
    this->kluczPodstawowy = kluczPodstawowy;
    this->macierze = new Macierze(tresc);
    rozszerzKlucz();
}

TekstJawny::~TekstJawny() {
    delete macierze;
}

unsigned int potega(unsigned int podstawa, unsigned int wykladnik) {
    unsigned int wynik = 1;
    for(int i=1; i<=wykladnik; i++) {
        wynik *= podstawa;
    }
    return wynik;
}

void TekstJawny::rozszerzKlucz() {
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

void TekstJawny::addRoundKey() {
    for(int i=0; i<iloscMacierzy; i++) {
        string roundKey = kluczRozszerzony.substr(i*16, i*16+15);

//        cout << "Klucz rundy: " << roundKey << endl;
//        unsigned char* uc = (unsigned char*)myString.c_str();
//        unsigned char* roundKey1 = (unsigned char*)roundKey.substr(0,3).c_str();
//        unsigned char* roundKey2 = (unsigned char*)roundKey.substr(4,7).c_str();
//        unsigned char* roundKey3 = (unsigned char*)roundKey.substr(8,11).c_str();
//        unsigned char* roundKey4 = (unsigned char*)roundKey.substr(12,15).c_str();

//        cout << "Przed xorem: " << endl;
//        macierze->wyswietlMacierze();

        for(int j=0; j<4; j++) {
            for(int k=0; k<4; k++) {
                macierze->macierze[i][j][k] ^= roundKey.at(j*4+k);
            }
        }
    }
}

