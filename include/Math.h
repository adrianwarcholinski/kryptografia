#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "BigInt.h"
#include <bitset>

class BigInt;

class Math {
private:
    Math();
public:
    static BigInt fastPower(BigInt base, BigInt modulo, BigInt exponent);
    static std::bitset<1024> DecToBin(BigInt number);
    static bool isPrime(BigInt n);
    static BigInt BinToDec(std::bitset<1024> number);
    static BigInt NWD(BigInt a, BigInt p);
};


#endif //PROGRAM_MATH_H
