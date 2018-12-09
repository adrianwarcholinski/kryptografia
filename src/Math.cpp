//
// Created by kamil on 30.11.18.
//

#include <Math.h>

#include "Math.h"

BigInt Math::fastPower(BigInt base, BigInt modulo, BigInt exponent) {
    bitset<1024> nBin = Math::DecToBin(exponent);
    BigInt y = 1;
    BigInt z = base % modulo;
    for(int i=0; i<1024; i++) {
        if(nBin[i] == 1) {
            y = (y*z) % modulo;
        }
        z = (z*z) % modulo;
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

bool Math::isPrime(BigInt n) { // Test pierwszosci Fermata - badamy, czy x^(n-1) przystaje do 1 (mod n)
    bool answer = true;
    string temp = "2985108";
    BigInt leftSide = fastPower(temp,  n , n-1);
    BigInt rightSide(1);

    if(leftSide != rightSide) {
        answer = false;
    }

    temp = "1981981981";
    leftSide = fastPower(temp,  n , n-1);
    rightSide = 1;

    if(leftSide != rightSide) {
        answer = false;
    }

    temp = "91005151848";
    leftSide = fastPower(temp,  n , n-1);
    rightSide = 1;

    if(leftSide != rightSide) {
        answer = false;
    }

    return answer;
}

BigInt Math::NWD(BigInt a, BigInt p) {
    cout << "Licze NWD" << endl;
    while(p != 0) {
        BigInt c = a % p;
        a = p;
        p = c;
    }
    cout << "Skonczylem liczyc NWD" << endl;
    return a;
}
