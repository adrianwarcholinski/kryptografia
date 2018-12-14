#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "DuzyInt.h"
#include <bitset>

class DuzyInt;

class Math {
public:
    static DuzyInt fastPower(DuzyInt base, DuzyInt modulo, DuzyInt exponent);
    static DuzyInt fastPower(DuzyInt base, DuzyInt exponent);
    static bool isPrime(DuzyInt n);
};


#endif //PROGRAM_MATH_H
