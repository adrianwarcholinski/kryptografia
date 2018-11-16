//
// Created by adria on 12.10.2018.
//

#ifndef PROJEKT_TEKSTJAWNY_H
#define PROJEKT_TEKSTJAWNY_H

#include <string>
#include "Macierze.h"

using namespace std;

class Tekst {
private:



    void rozszerzKlucz();
public:
    string kluczPodstawowy;
    string kluczRozszerzony;
    string tresc;
    Macierze* macierze;
    Tekst(string kluczPodstawowy,string tresc);
    ~Tekst();
    void addRoundKey(int round);
    int getIloscMacierzy() const;
};


#endif //PROJEKT_TEKSTJAWNY_H
