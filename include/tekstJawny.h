//
// Created by adria on 12.10.2018.
//

#include <string>

#ifndef PROJEKT_TEKSTJAWNY_H
#define PROJEKT_TEKSTJAWNY_H

using namespace std;

class tekstJawny{
private:
    string tresc;
    int iloscMacierzy;
    char ***macierze;
    void wypelnijMacierze();
    void utworzMacierze();
    void usunMacierze();
public:
    tekstJawny(string tresc);
    ~tekstJawny();
    void wyswietlMacierze();
};


#endif //PROJEKT_TEKSTJAWNY_H
