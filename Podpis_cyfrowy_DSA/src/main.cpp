#include <string>
#include <iostream>

#include "../include/DuzyInt.h"
#include "../include/Math.h"
#include "MD5Hash.cpp"

using namespace std;

int main() {
    string szyfrowanyTekst = "ALA MA KOTA";

    // CZYNNOŚCI WSTĘPNE
    DuzyInt p("17801190547854226652823756245015999014523215636912067427327445031"
              "444286578873702077061269525212346307956715678477846644997065077092072"
              "785705000966838814403412974522117181850604723115003930107995935806739"
              "534871706631980226201971496652413506094591370759495651467285569060679"
              "4135837542707371727429551343320695239");   // 1024-bitowa
    DuzyInt q("864205495604807476120572616017955259175325408501");   // 160-bitowa, p-1 podzielne przez q

    DuzyInt h("17406820753240209518581198012352343653860449079456135097849583104"
              "059995348845582314785159740894095072530779709491575949236830057425243"
              "876103708447346718014887611810308304375498519098347260155049469132948"
              "808339549231385000036164648264460849230407872181895999905649609776936"
              "8017749273708962006689187956744210730");   // h < p-1
    DuzyInt a("11413953692062257086993806233172330674938775529337393031977771373"
                          "129746946910914240113023221721777732136818444139744393157698465044933"
                          "013442758757568273862367115354816009554808091206304096963365266649829"
                          "966917085474283297375073085459703201287235180005340124397005934806133"
                          "1526243448471205166130497310892424132");   // a < q

    cout << "p = " << p << endl
         << "q = " << q << endl
         << "h = " << h << endl
         << "a = " << a << endl;

    if(Math::isPrime(p)) {
        cout << "Liczba p przeszla test pierwszosci" << endl;
        if(Math::isPrime(q)) {
            cout << "Liczba q przeszla test pierwszosci" << endl;
            if((p-1) % q == 0) {
                cout << "Liczba p-1 jest podzielna przez q " << endl;
                DuzyInt b = Math::fastPower(h, p, a);   // b = h^a mod p
                cout << "b = " << b << endl;

                // KONIEC CZYNNOŚCI WSTĘPNYCH

                // GENEROWANIE PODPISU
                cout << "-------------------------\nGENEROWANIE PODPISU...\n-----------------------------------" << endl;
                DuzyInt r("774290984479563168206130828532207106685994961942");
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
                DuzyInt t = Math::fastPower(h, p, u1) * Math::fastPower(b, p, u2) % p % q;
                cout << "t = " << t << endl;
                if(t == s1) {
                    cout << "PODPIS ZAAKCEPTOWANY" << endl;
                } else {
                    cout << "PODPIS ODRZUCONY" << endl;
                }
                // KONIEC WERYFIKACJI
            } else {
                cout << "Liczba p-1 nie jest podzielna przez q" << endl;
            }
        } else {
            cout << "Liczba q nie jest pierwsza" << endl;
        }
    } else {
        cout << "Liczba p nie jest pierwsza" << endl;
    }

    system("PAUSE");
    return 0;
}