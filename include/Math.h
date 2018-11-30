#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "BigInt.h"
#include <bitset>

class Math {
private:
    Math();
public:
static BigInt fastPower(BigInt x, BigInt m, BigInt n);
static bitset<1024> dec2Bin(BigInt x);
static bool isPrime(BigInt x);
};


#endif //PROGRAM_MATH_H
