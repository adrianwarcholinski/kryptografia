//
// Created by adria on 26.10.2018.
//

#ifndef PROGRAM_MACIERZE_H
#define PROGRAM_MACIERZE_H

#include <string>

using namespace std;

class Macierze {


public:
    unsigned char*** macierze;   //macierze[i][j][k]: i-numer macierzy stanu;j-numer wiersza w macierzy stanu;k- numer kolumny w macierzy stanu.
    Macierze(string tekst);
    ~Macierze();
    void wyswietlMacierze();


    int liczbaMacierzyStanu;
    void utworzMacierze(string tekst);
    void wypelnijMacierze(string tekst);
    void usunMacierze();
    void shiftRows();
    void substituteBytes();
    void mixColumns();
    void inverseShiftRows();
    void inverseSubstituteBytes();
    void inverseMixColumns();


};


#endif //PROGRAM_MACIERZE_H
