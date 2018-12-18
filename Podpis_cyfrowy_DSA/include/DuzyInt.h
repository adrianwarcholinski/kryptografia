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

class DuzyInt {
public:
    string liczba;
    bool znak;
public:
    // Konstruktory
    DuzyInt();
    DuzyInt(int n);
    DuzyInt(const string & s);

    // Operator przypisania
    DuzyInt & operator=(const DuzyInt & b);

    // Gettery i settery
    const string & getLiczba() const;
    bool getZnak() const;
    void setLiczba(const string &number);
    void setZnak(bool sign);

    // działania
    const DuzyInt wartosc_bezwzgledna() const;
    const string dodaj(const string &num1, const string &num2) const;
    const string odejmij(const string &num1, const string &num2) const;
    const string pomnoz(const string &num1, const string &num2) const;
    const string podziel(const string &num, long long divisor) const;
    const string modulo(string num, long a) const;

    // operatory matematyczne
    const DuzyInt operator+(const DuzyInt & b) const;
    const DuzyInt operator-(const DuzyInt & b) const;
    const DuzyInt operator*(const DuzyInt & b) const;
    const DuzyInt operator/(const DuzyInt & b) const;
    const DuzyInt operator%(const DuzyInt & b) const;
    const DuzyInt operator-() const;
    const char operator[](int n) const;

    // operatory logiczne
    bool operator==(const DuzyInt & b) const;
    bool operator!=(const DuzyInt & b) const;
    bool operator>(const DuzyInt & b) const;
    bool operator<(const DuzyInt & b) const;
    bool operator>=(const DuzyInt & b) const;
    bool operator<=(const DuzyInt & b) const;

    friend ostream & operator<<(ostream & os, const DuzyInt & b);
private:
    bool rowne(const DuzyInt &n1, const DuzyInt &n2) const;
    bool mniejsze(const DuzyInt &n1, const DuzyInt &n2) const;
    bool wieksze(const DuzyInt &n1, const DuzyInt &n2) const;
};

#endif //ZAD_2_RSA_BIGINT_H
