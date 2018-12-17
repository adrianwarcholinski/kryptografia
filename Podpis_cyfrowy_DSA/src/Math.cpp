//
// Created by kamil on 30.11.18.
//

#include "../include/Math.h"
#include "../include/DuzyInt.h"

DuzyInt Math::fastPower(DuzyInt base, DuzyInt modulo, DuzyInt exponent) {
//    bitset<1024> nBin = Math::DecToBin(exponent);
//    DuzyInt y = 1;
//    DuzyInt z = base % modulo;
//    for(int i=0; i<1024; i++) {
//        if(nBin[i] == 1) {
//            y = (y*z) % modulo;
//        }
//        z = (z*z) % modulo;
//    }
//    return y;

    DuzyInt y = 1;
    DuzyInt z = base % modulo;
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