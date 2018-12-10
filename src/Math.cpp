//
// Created by kamil on 30.11.18.
//

#include <Math.h>

#include "Math.h"

BigInt Math::fastPower(BigInt base, BigInt modulo, BigInt exponent) {
//    bitset<1024> nBin = Math::DecToBin(exponent);
//    BigInt y = 1;
//    BigInt z = base % modulo;
//    for(int i=0; i<1024; i++) {
//        if(nBin[i] == 1) {
//            y = (y*z) % modulo;
//        }
//        z = (z*z) % modulo;
//    }
//    return y;

    BigInt y = 1;
    BigInt z = base % modulo;
    bool isZero;

    while(exponent > 0) {
        if(exponent % 2 == 0) {
            isZero = true;
        } else {
            isZero = false;
        }
        exponent = exponent / 2;
        if(isZero == false) {
            y = (y*z) % modulo;
        }
        z = (z*z) % modulo;
    }
    return y;
}

BigInt Math::fastPower(BigInt base, BigInt exponent) {
    BigInt y = 1;
    BigInt z = base;
    bool isZero;

    while(exponent > 0) {
        if(exponent % 2 == 0) {
            isZero = true;
        } else {
            isZero = false;
        }
        exponent = exponent / 2;
        if(isZero == false) {
            y = (y*z);
        }
        z = (z*z);
    }
    return y;
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