//
// Created by Krystian on 17.11.2018.
//

#include <iostream>
#include "DuzyInt.h"

// Konstruktory
DuzyInt::DuzyInt() {
    liczba = "0";
    znak = false;
}

DuzyInt::DuzyInt(int n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;

    if (isdigit(s[0])) // if not signed
    {
        setLiczba(s);
        setZnak(false); // +ve
    }
    else {
        setLiczba(s.substr(1));
        setZnak(s[0] == '-');
    }
}

DuzyInt::DuzyInt(const string & s) {
    if (isdigit(s[0])) // if not signed
    {
        setLiczba(s);
        znak = false; // +ve
    }
    else {
        setLiczba(s.substr(1));
        znak = (s[0] == '-');
    }
}

// Operator przypisania
DuzyInt & DuzyInt::operator=(const DuzyInt & b) {
    setLiczba(b.getLiczba());
    setZnak(b.getZnak());
    return *this;
}

// Gettery i settery
const string & DuzyInt::getLiczba() const { return liczba; }

bool DuzyInt::getZnak() const { return znak; }

void DuzyInt::setLiczba(const string &number) { liczba = number; }

void DuzyInt::setZnak(bool s) { znak = s; }

// działania
const DuzyInt DuzyInt::wartosc_bezwzgledna() const {
    return DuzyInt(getLiczba());
}

const string DuzyInt::dodaj(const string &num1, const string &num2) const {
    string number1 = num1;
    string number2 = num2;
    string add = (number1.length() > number2.length()) ? number1 : number2;
    char carry = '0';
    int differenceInLength = abs((int) (number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else// if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.size() - 1; i >= 0; --i) {
        add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

        if (i != 0) {
            if (add[i] > '9') {
                add[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    if (add[0] > '9') {
        add[0] -= 10;
        add.insert(0, 1, '1');
    }
    return add;
}

const string DuzyInt::odejmij(const string &num1, const string &num2) const {
    string number1 = num1;
    string number2 = num2;

    string sub = (number1.length() > number2.length()) ? number1 : number2;
    int differenceInLength = abs((int) (number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.length() - 1; i >= 0; --i) {
        if (number1[i] < number2[i]) {
            number1[i] += 10;
            number1[i - 1]--;
        }
        sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
    }

    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);

    return sub;
}

const string DuzyInt::pomnoz(const string &num1, const string &num2) const {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    // will keep the result liczba in vector
    // in reverse order
    vector<int> result(n1 + n2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = num1[i] - '0';

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (int j = n2 - 1; j >= 0; j--) {
            // Take current digit of second liczba
            int n2 = num2[j] - '0';

            // Multiply with current digit of first liczba
            // and dodaj result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
        return "0";

    // generate the result string
    string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}

const string DuzyInt::podziel(const string &num, long long divisor) const {
    // As result can be very large store it in string
    string ans;

    // Find prefix of liczba that is larger
    // than divisor.
    int idx = 0;
    int temp = liczba[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (liczba[++idx] - '0');

    // Repeatedly podziel divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (liczba.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of liczba
        temp = (temp % divisor) * 10 + liczba[++idx] - '0';
    }

    // If divisor is wieksze than liczba
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}

const string DuzyInt::modulo(string num, long a) const {
    // Initialize result
    int res = 0;
    string r;
    // One by one process all digits of 'num'
    for (int i = 0; i < num.length(); i++)
        res = (res * 10 + (int) num[i] - '0') % a;
    r = to_string(res);
    return r;
}

// operatory matematyczne
const DuzyInt DuzyInt::operator+(const DuzyInt & b) const {
    DuzyInt addition;
    if (getZnak() == b.getZnak()) // both +ve or -ve
    {
        addition.setLiczba(dodaj(getLiczba(), b.getLiczba()));
        addition.setZnak(getZnak());
    }
    else // znak different
    {
        if (wartosc_bezwzgledna() > b.wartosc_bezwzgledna()) {
            addition.setLiczba(odejmij(getLiczba(), b.getLiczba()));
            addition.setZnak(getZnak());
        }
        else {
            addition.setLiczba(odejmij(b.getLiczba(), getLiczba()));
            addition.setZnak(b.getZnak());
        }
    }
    if (addition.getLiczba() == "0") // avoid (-0) problem
        addition.setZnak(false);

    return addition;
}

const DuzyInt DuzyInt::operator-(const DuzyInt & b) const {
    DuzyInt temp = b;
    temp.setZnak(!b.getZnak()); // x - y = x + (-y)
    return (*this) + temp;
}

const DuzyInt DuzyInt::operator*(const DuzyInt & b) const {
    DuzyInt mul;

    mul.setLiczba(pomnoz(getLiczba(), b.getLiczba()));
    mul.setZnak(getZnak() != b.getZnak());

    if (mul.getLiczba() == "0") // avoid (-0) problem
        mul.setZnak(false);

    return mul;
}

const DuzyInt DuzyInt::operator/(const DuzyInt & b) const {
    DuzyInt res;
    string num1, num2;
    if (getZnak() == true) num1 += "-";
    num1 += getLiczba();
    if (b.getZnak() == true) num2 += "-";
    num2 += b.getLiczba();
    cpp_int n1(num1);
    cpp_int n2(num2);
    n1 = n1 / n2;
    res = n1.convert_to<string>();
    return res;
}

const DuzyInt DuzyInt::operator%(const DuzyInt & b) const {
    DuzyInt res;
    string num1, num2;
    if (getZnak() == true) num1 += "-";
    num1 += getLiczba();
    if (b.getZnak() == true) num2 += "-";
    num2 += b.getLiczba();
    cpp_int n1(num1);
    cpp_int n2(num2);
    n1 = n1 % n2;
    res = n1.convert_to<string>();
    return res;
}

const DuzyInt DuzyInt::operator-() const {
    return (*this) * -1;
}

const char DuzyInt::operator[](int n) const {
    string number = getLiczba();
    return number[n];
}

// operatory logiczne
bool DuzyInt::operator==(const DuzyInt & b) const {
    return rowne((*this), b);
}

bool DuzyInt::operator!=(const DuzyInt & b) const {
    return !rowne((*this), b);
}

bool DuzyInt::operator>(const DuzyInt & b) const {
    return wieksze((*this), b);
}

bool DuzyInt::operator<(const DuzyInt & b) const {
    return mniejsze((*this), b);
}

bool DuzyInt::operator>=(const DuzyInt & b) const {
    return rowne((*this), b)
           || wieksze((*this), b);
}

bool DuzyInt::operator<=(const DuzyInt & b) const {
    return rowne((*this), b)
           || mniejsze((*this), b);

}

ostream & operator<<(ostream & os, const DuzyInt & b) {
    if (b.znak == true) os << '-' << b.liczba;
    else os << b.liczba;
    return os;
}

bool DuzyInt::rowne(const DuzyInt &n1, const DuzyInt &n2) const {
    return n1.getLiczba() == n2.getLiczba() && n1.getZnak() == n2.getZnak();
}

bool DuzyInt::mniejsze(const DuzyInt &n1, const DuzyInt &n2) const {
    bool sign1 = n1.getZnak();
    bool sign2 = n2.getZnak();

    if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if (!sign1 && sign2)
        return false;

    else if (!sign1) // both +ve
    {
        if (n1.getLiczba().length() < n2.getLiczba().length())
            return true;
        if (n1.getLiczba().length() > n2.getLiczba().length())
            return false;
        return n1.getLiczba() < n2.getLiczba();
    }
    else // both -ve
    {
        if (n1.getLiczba().length() > n2.getLiczba().length())
            return true;
        if (n1.getLiczba().length() < n2.getLiczba().length())
            return false;
        return n1.getLiczba().compare(n2.getLiczba()) > 0; // wieksze with -ve znak is LESS
    }
}

bool DuzyInt::wieksze(const DuzyInt &n1, const DuzyInt &n2) const {
    return !rowne(n1, n2) && !mniejsze(n1, n2);
}






