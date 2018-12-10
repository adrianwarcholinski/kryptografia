#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "BigInt.h"
#include <bitset>

class BigInt;

class Math {
public:
    static BigInt fastPower(BigInt base, BigInt modulo, BigInt exponent);
    static BigInt fastPower(BigInt base, BigInt exponent);
    static bool isPrime(BigInt n);
};


#endif //PROGRAM_MATH_H
