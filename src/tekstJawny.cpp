//
// Created by adria on 12.10.2018.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "tekstJawny.h"
#include <cmath>

tekstJawny::tekstJawny(string tresc) {
    this->tresc = tresc;
    utworzMacierze();
    wypelnijMacierze();
}
tekstJawny::~tekstJawny() {
    usunMacierze();
}
void tekstJawny::wyswietlMacierze() {
    for (int i = 0; i < iloscMacierzy; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                cout << macierze[i][j][k];
            }
            cout << endl;
        }
        cout<<endl;
    }
}
void tekstJawny::wypelnijMacierze() {
    int licznik = 0;
    for (int i = 0; i < iloscMacierzy; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (tresc.length() <= licznik)
                    macierze[i][j][k] = '0';
                else
                    macierze[i][j][k] = tresc[licznik];
                licznik++;
            }
        }
    }
}
    void tekstJawny::utworzMacierze()
    {
        iloscMacierzy = int(ceil(tresc.length() * 1.0 / 16));
        macierze = new char**[iloscMacierzy];
        for(int i(0); i < iloscMacierzy; ++i)
        {
            macierze[i] = new char*[4];

            for(int j(0); j < 4; ++j)
            {
                macierze[i][j] = new char[4];
            }
        }
    }
    void tekstJawny::usunMacierze(){
        {
            for (int i = 0; i < iloscMacierzy; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    delete [] macierze[i][j];
                }
                delete [] macierze[i];
            }
            delete [] macierze;
        }
    }

