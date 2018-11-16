//
// Created by adria on 12.10.2018.
//

#ifndef PROJEKT_TEKSTJAWNY_H
#define PROJEKT_TEKSTJAWNY_H

#include <string>
#include "Macierze.h"

using namespace std;

class TekstJawny {
private:
    string tresc;
    int iloscMacierzy;
    string kluczPodstawowy;
    string kluczRozszerzony;

    void rozszerzKlucz();
public:
    Macierze* macierze;
    TekstJawny(string kluczPodstawowy,string tresc);
    ~TekstJawny();
    void addRoundKey(int round);
};


#endif //PROJEKT_TEKSTJAWNY_H
