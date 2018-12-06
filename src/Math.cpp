//
// Created by kamil on 30.11.18.
//

#include <Math.h>

#include "Math.h"

BigInt Math::fastPower(BigInt base, BigInt power, BigInt modulo) {
    bitset<1024> binpower(Math::DecToBin(power));
    BigInt y=1;
    BigInt z=base%modulo;
    for(int i=0;i<1024;++i){
    if(binpower[i]==1){
        y=y*z%int(binpower[i]);
    }
    z=z*z%modulo;
    }
    return y;
}

bitset<1024> Math::DecToBin(BigInt number)
{
    int bit=0;
    bitset<1024> bitset;
    while(number>0 && bit<1024){
        if(number%2==0){
            bitset[bit]=0;
        }
        else{
            bitset[bit]=1;
        }
        number=number/2;
        ++bit;
    }
return bitset;
}

BigInt Math::BinToDec(bitset<1024> number)
{
    BigInt result=0;
    BigInt pow=1;
    for(int i=0; i<1024; ++i, pow=pow*2 )
        result=result+BigInt(number[i])*pow;
    return result;
}

bool Math::isPrime(BigInt x) {
    return false;
}
