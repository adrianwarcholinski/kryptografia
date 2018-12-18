#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "DuzyInt.h"
#include <bitset>

class DuzyInt;

#define LICZBA_BITOW 10000

typedef bitset<LICZBA_BITOW> Bits;

class Math {
public:
    static DuzyInt fastPower(DuzyInt base, DuzyInt modulo, DuzyInt exponent);
    static DuzyInt fastPower(DuzyInt base, DuzyInt exponent);
    static Bits DecToBin(DuzyInt number);
    static DuzyInt BinToDec(Bits number);
    static DuzyInt NWD(DuzyInt a, DuzyInt b);
    static bool isPrime(DuzyInt n);
};


#endif //PROGRAM_MATH_H
