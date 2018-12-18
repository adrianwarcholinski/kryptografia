//
// Created by kamil on 30.11.18.
//

#include "../include/Math.h"
#include "../include/DuzyInt.h"

DuzyInt Math::fastPower(DuzyInt base, DuzyInt modulo, DuzyInt exponent) {
    DuzyInt y = 1;
    DuzyInt z = base % modulo;
    bool isZero;

    while(exponent > 0) {
        if (exponent % 2 == 0) {
            isZero = true;
        } else {
            isZero = false;
        }
        exponent = exponent / 2;
        if (isZero == false) {
            y = (y * z) % modulo;
        }
        z = (z * z) % modulo;
    }
    return y;
}

DuzyInt Math::fastPower(DuzyInt base, DuzyInt exponent) {
    DuzyInt y = 1;
    DuzyInt z = base;
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

Bits Math::DecToBin(DuzyInt number) {
    int bit=0;
    Bits bitset;
    while(number>0 && bit<LICZBA_BITOW){
        if(number%2==0){
            bitset[bit]=0;
        } else {
            bitset[bit]=1;
        }
        number=number/2;
        ++bit;
    }
    return bitset;
}

DuzyInt Math::BinToDec(Bits number) {
    DuzyInt result = 0;
    DuzyInt pow = 1;
    for (int i = 0; i < LICZBA_BITOW; ++i, pow = pow * 2)
        result = result + DuzyInt(number[i]) * pow;
    return result;
}

bool Math::isPrime(DuzyInt n) { // Test pierwszosci Fermata - badamy, czy x^(n-1) przystaje do 1 (mod n)
    bool answer = true;
    string temp = "201";
    DuzyInt leftSide = fastPower(temp,  n , n-1);
    DuzyInt rightSide(1);

    if(leftSide != rightSide) {
        answer = false;
    }

    temp = "147";
    leftSide = fastPower(temp,  n , n-1);
    rightSide = 1;

    if(leftSide != rightSide) {
        answer = false;
    }

    temp = "3";
    leftSide = fastPower(temp,  n , n-1);
    rightSide = 1;

    if(leftSide != rightSide) {
        answer = false;
    }

    return answer;
}

DuzyInt Math::NWD(DuzyInt a, DuzyInt b) {
    while(b != 0) {
        DuzyInt t = b;
        b = a % b;
        a = t;
    }
    return a;
}
