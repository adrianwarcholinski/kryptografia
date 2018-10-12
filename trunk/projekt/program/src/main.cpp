#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
class obiekt_do_szyfrowania{
private:
    char* tresc;
    bool opcja;
public:
    obiekt_do_szyfrowania(){
        cout<<"Prosze podac metode wprowadzania danych:\n1. Tekst wprowadzany z klawiatury\n2. Tekst wczytywany z pliku\nWpisz wybraną opcje:    ";
        cin>>opcja;
        cout<<opcja;
        }

};
int main() {
    cout << "Algorytm szyfrowania AES. \n Autorzy:\n- Aleksandra Ruta\n-Adrian Warcholinski\n- Kamil Piatkowski" << endl;
    obiekt_do_szyfrowania ob;
    return 0;
}