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
    delete[] macierze;
}

void TekstJawny::rozszerzKlucz() {
    SBox* sbox = new SBox();
    this->kluczRozszerzony = kluczPodstawowy;

    for(int iteracja=1; iteracja<=10; iteracja++) {
        vector<char> tempVector(4);
        for(int i=0; i<tempVector.size(); i++) {
            tempVector[i] = kluczPodstawowy[kluczPodstawowy.length()-4+i];
        }
        for(int i=0; i<tempVector.size()-1; i++) {
            swap(tempVector[i],tempVector[i+1]);
        }
        for(int i=0; i<tempVector.size(); i++) {
            cout << "tempVector: " << (int)tempVector[i] << " podmieniony na ";
            tempVector[i] = sbox->nowyBajtNormalny(tempVector[i]);
            cout << hex << (int)tempVector[i] << endl;
        }
    }
}

