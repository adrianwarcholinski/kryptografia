#ifndef PROGRAM_SBOX_H
#define PROGRAM_SBOX_H

class SBox {
private:
    unsigned char** tabelaNormalna;
    unsigned char** tabelaOdwrocona;

    void wczytajSBox();
public:
    SBox();
    ~SBox();
    void wyswietlSBoxy();
    unsigned char nowyBajtNormalny(unsigned char bajt);
    unsigned char nowyBajtOdwrocony(unsigned char bajt);
};


#endif //PROGRAM_SBOX_H