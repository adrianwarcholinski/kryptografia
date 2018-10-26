//
// Created by adria on 26.10.2018.
//

#ifndef PROGRAM_MACIERZE_H
#define PROGRAM_MACIERZE_H

#include <string>

using namespace std;

class Macierze {
public:
    int liczbaMacierzy;
    char*** macierze;

    Macierze(string tekst);
    void wyswietlMacierze();
    void wypelnijMacierze(string tekst);
    void utworzMacierze(string tekst);
};


#endif //PROGRAM_MACIERZE_H
