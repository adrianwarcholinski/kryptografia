//
// Created by adria on 12.10.2018.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "TekstJawny.h"
#include <cmath>
#include <vector>

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
    this->kluczRozszerzony = kluczPodstawowy;
    vector<char> tempVector(4);
    for(int i=0; i<tempVector.size(); i++) {
        tempVector[i] = kluczPodstawowy[kluczPodstawowy.length()-4+i];
    }
    for(int i=0; i<tempVector.size()-1; i++) {
        swap(tempVector[i],tempVector[i+1]);
    }
}

