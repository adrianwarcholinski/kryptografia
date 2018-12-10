//
// Created by Krystian on 17.11.2018.
//

#ifndef ZAD_2_RSA_BIGINT_H
#define ZAD_2_RSA_BIGINT_H

#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

class BigInt {
private:
    string number;
    bool sign;
public:
    // Konstruktory
    BigInt();
    BigInt(int n);
    BigInt(const string & s);

    // Operator przypisania
    BigInt & operator=(const BigInt & b);

    // Gettery i settery
    const string & getNumber() const;
    bool getSign() const;
    void setNumber(const string & number);
    void setSign(bool sign);

    // działania
    const BigInt absolute() const;
    const string add(const string & num1, const string & num2) const;
    const string subtract(const string & num1, const string & num2) const;
    const string multiply(const string & num1, const string & num2) const;
    const string divide(const string & num, long long divisor) const;
    const string modulo(string num, long a) const;

    // operatory matematyczne
    const BigInt operator+(const BigInt & b) const;
    const BigInt operator-(const BigInt & b) const;
    const BigInt operator*(const BigInt & b) const;
    const BigInt operator/(const BigInt & b) const;
    const BigInt operator%(const BigInt & b) const;
    const BigInt operator-() const;
    const char operator[](int n) const;

    // operatory logiczne
    bool operator==(const BigInt & b) const;
    bool operator!=(const BigInt & b) const;
    bool operator>(const BigInt & b) const;
    bool operator<(const BigInt & b) const;
    bool operator>=(const BigInt & b) const;
    bool operator<=(const BigInt & b) const;

    friend ostream & operator<<(ostream & os, const BigInt & b);
private:
    bool equals(const BigInt & n1, const BigInt & n2) const;
    bool less(const BigInt & n1, const BigInt & n2) const;
    bool greater(const BigInt & n1, const BigInt & n2) const;
};

#endif //ZAD_2_RSA_BIGINT_H
