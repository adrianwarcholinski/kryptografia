#ifndef PROGRAM_MATH_H
#define PROGRAM_MATH_H

#include "BigInt.h"

class Math {
private:
    Math();
public:
static BigInt fastPower(BigInt x, BigInt m, BigInt n);
};


#endif //PROGRAM_MATH_H
