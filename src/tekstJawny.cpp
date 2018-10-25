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
    this->iloscMacierzy = int(ceil(tresc.length() * 1.0 / 16));
    podzialNaMacierze();
}
tekstJawny::~tekstJawny() {
    usunMacierze(macierze, iloscMacierzy);
    cout<<"Macierze usuniete"<<endl;
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
void tekstJawny::podzialNaMacierze() {
    this->macierze = utworzMacierze(iloscMacierzy);
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
    char*** tekstJawny::utworzMacierze(int iloscMacierzy)
    {
        char*** the_array = new char**[iloscMacierzy];
        for(int i(0); i < iloscMacierzy; ++i)
        {
            the_array[i] = new char*[4];

            for(int j(0); j < 4; ++j)
            {
                the_array[i][j] = new char[4];
            }
        }
        return the_array;
    }
    void tekstJawny::usunMacierze(char*** the_array, int iloscMacierzy){
        {
            for (int i = 0; i < iloscMacierzy; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    delete [] the_array[i][j];
                }
                delete [] the_array[i];
            }
            delete [] the_array;
        }
    }

