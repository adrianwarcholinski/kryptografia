#include <iostream>
#include <string>

#include "MD5Hash.cpp"
#include "../include/DuzyInt.h"
#include "../include/Math.h"

using namespace std;

int main() {
    DuzyInt p(97);   // 1024-bitowa
    DuzyInt q(48);   // 160-bitowa, p-1 podzielne przez q
    DuzyInt h(30);   // h < p-1
    DuzyInt a(25);   // a < q

    DuzyInt b = Math::fastPower(h, p, a);   // b = h^a mod p

    // CZYNNOŚCI WSTĘPNE
    cout << "Czynnosci wstepne..." << endl;
    cout << "Klucz publiczny: " << endl
         << "p = " << p << endl
         << "q = " << q << endl
         << "h = " << h << endl
         << "b = " << b << endl
         << "Klucz prywatny: " << endl
         << "a = " << a << endl;
    // KONIEC CZYNNOŚCI WSTĘPNYCH



    return 0;
}