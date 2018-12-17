#include <iostream>
#include <string>

#include "MD5Hash.cpp"
#include "../include/DuzyInt.h"
#include "../include/Math.h"

using namespace std;

int main() {
    string szyfrowanyTekst = "ALA MA KOTA";


    // CZYNNOŚCI WSTĘPNE
    DuzyInt p(107);   // 1024-bitowa
    DuzyInt q(53);   // 160-bitowa, p-1 podzielne przez q
    DuzyInt h(30);   // h < p-1
    DuzyInt a(25);   // a < q

    DuzyInt b = Math::fastPower(h, p, a);   // b = h^a mod p

    cout << "------------------------\nCZYNNOSCI WSTEPNE...\n-----------------------------------" << endl;
    cout << "Klucz publiczny: " << endl
         << "p = " << p << endl
         << "q = " << q << endl
         << "h = " << h << endl
         << "b =  " << b << endl
         << "Klucz prywatny: " << endl
         << "a = " << a << endl;
    // KONIEC CZYNNOŚCI WSTĘPNYCH

    // GENEROWANIE PODPISU
    cout << "-------------------------\nGENEROWANIE PODPISU...\n-----------------------------------" << endl;
    DuzyInt r(26);  // r <= p-1
    cout << "r = " << r << endl;
    cout << "Wyznaczam r'..." << endl;
    DuzyInt rPrim = Math::fastPower(r, q, q-2); // rPrim = r^-1 mod q = r^(q-2) mod q
    cout << "rPrim = " << rPrim << endl;
    cout << "Wyznaczam s1..." << endl;
    DuzyInt s1 = Math::fastPower(h, p, r) % q;
    cout << "Obliczam wartosc funkcji haszujacej..." << endl;
    DuzyInt funkcjaHaszujaca(GetMD5String(szyfrowanyTekst));
    cout << "Wartosc funkcji haszujacej = " << hex << funkcjaHaszujaca << dec << endl;
    cout << "Wyznaczam s2..." << endl;
    DuzyInt s2 = (rPrim * (funkcjaHaszujaca + a*s1)) % q;

    cout << "Podpis cyfrowy: " << endl
         << "s1 = " << s1 << endl
         << "s2 = " << s2 << endl;
    // KONIEC GENEROWANIA PODPISU

    // WERYFIKACJA
    cout << "-------------------------\nWERYFIKACJA PODPISU...\n-----------------------------------" << endl;
    cout << "Wyznaczam s'..." << endl;
    DuzyInt sPrim = Math::fastPower(s2, q, q-2);
    cout << "s' = " << sPrim << endl;
    cout << "Wyznaczam u1..." << endl;
    DuzyInt u1 = (funkcjaHaszujaca * sPrim) % q;
    cout << "u1 = " << u1 << endl;
    cout << "Wyznaczam u2..." << endl;
    DuzyInt u2 = (sPrim * s1) % q;
    cout << "u2 = " << u2 << endl;
    cout << "Wyznaczam t..." << endl;
    DuzyInt t = (Math::fastPower(h, u1) * Math::fastPower(b, u2)) % p % q;
    cout << "t = " << t << endl;
    if(t == s1) {
        cout << "PODPIS ZAAKCEPTOWANY" << endl;
    } else {
        cout << "PODPIS ODRZUCONY" << endl;
    }
    // KONIEC WERYFIKACJI

    return 0;
}