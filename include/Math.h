#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "BigInt.h"
#include <bitset>

class Math {
private:
    Math();
public:
static BigInt fastPower(BigInt base, BigInt power, BigInt modulo);
static bitset<1024> DecToBin(BigInt number);
static bool isPrime(BigInt x);
static BigInt BinToDec(bitset<1024> number);
};


#endif //PROGRAM_MATH_H
