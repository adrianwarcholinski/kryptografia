//
// Created by adria on 26.10.2018.
//

#ifndef PROGRAM_SBOX_H
#define PROGRAM_SBOX_H

class SBox {
private:
    char** tabelaNormalna;
    char** tabelaOdwrocona;
    void wczytajSBox();
public:
    SBox();
    ~SBox();
    void wyswietlSBoxy();
    char nowyBajtNormalny(char bajt);
    char nowyBajtOdwrocony(char bajt);
};


#endif //PROGRAM_SBOX_H
