//
// Created by Krystian on 17.11.2018.
//

#include <iostream>
#include "BigInt.h"

// Konstruktory
BigInt::BigInt() {
    number = "0";
    sign = false;
}

BigInt::BigInt(int n) {
    stringstream ss;
    string s;
    ss << n;
    ss >> s;

    if (isdigit(s[0])) // if not signed
    {
        setNumber(s);
        setSign(false); // +ve
    }
    else {
        setNumber(s.substr(1));
        setSign(s[0] == '-');
    }
}

BigInt::BigInt(const string & s) {
    if (isdigit(s[0])) // if not signed
    {
        setNumber(s);
        sign = false; // +ve
    }
    else {
        setNumber(s.substr(1));
        sign = (s[0] == '-');
    }
}

// Operator przypisania
BigInt & BigInt::operator=(const BigInt & b) {
    setNumber(b.getNumber());
    setSign(b.getSign());
    return *this;
}

// Gettery i settery
const string & BigInt::getNumber() const { return number; }

bool BigInt::getSign() const { return sign; }

void BigInt::setNumber(const string & n) { number = n; }

void BigInt::setSign(bool s) { sign = s; }

// działania
const BigInt BigInt::absolute() const {
    return BigInt(getNumber());
}

const string BigInt::add(const string & num1, const string & num2) const {
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

const string BigInt::subtract(const string & num1, const string & num2) const {
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

const string BigInt::multiply(const string & num1, const string & num2) const {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    // will keep the result number in vector
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
            // Take current digit of second number
            int n2 = num2[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
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

const string BigInt::divide(const string & num, long long divisor) const {
    // As result can be very large store it in string
    string ans;

    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";

    // else return ans
    return ans;
}

const string BigInt::modulo(string num, long a) const {
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
const BigInt BigInt::operator+(const BigInt & b) const {
    BigInt addition;
    if (getSign() == b.getSign()) // both +ve or -ve
    {
        addition.setNumber(add(getNumber(), b.getNumber()));
        addition.setSign(getSign());
    }
    else // sign different
    {
        if (absolute() > b.absolute()) {
            addition.setNumber(subtract(getNumber(), b.getNumber()));
            addition.setSign(getSign());
        }
        else {
            addition.setNumber(subtract(b.getNumber(), getNumber()));
            addition.setSign(b.getSign());
        }
    }
    if (addition.getNumber() == "0") // avoid (-0) problem
        addition.setSign(false);

    return addition;
}

const BigInt BigInt::operator-(const BigInt & b) const {
    BigInt temp = b;
    temp.setSign(!b.getSign()); // x - y = x + (-y)
    return (*this) + temp;
}

const BigInt BigInt::operator*(const BigInt & b) const {
    BigInt mul;

    mul.setNumber(multiply(getNumber(), b.getNumber()));
    mul.setSign(getSign() != b.getSign());

    if (mul.getNumber() == "0") // avoid (-0) problem
        mul.setSign(false);

    return mul;
}

const BigInt BigInt::operator/(const BigInt & b) const {
    BigInt res;
    string num1, num2;
    if (getSign() == true) num1 += "-";
    num1 += getNumber();
    if (b.getSign() == true) num2 += "-";
    num2 += b.getNumber();
    cpp_int n1(num1);
    cpp_int n2(num2);
    n1 = n1 / n2;
    res = n1.convert_to<string>();
    return res;
}

const BigInt BigInt::operator%(const BigInt & b) const {
    BigInt res;
    string num1, num2;
    if (getSign() == true) num1 += "-";
    num1 += getNumber();
    if (b.getSign() == true) num2 += "-";
    num2 += b.getNumber();
    cpp_int n1(num1);
    cpp_int n2(num2);
    n1 = n1 % n2;
    res = n1.convert_to<string>();
    return res;
}

const BigInt BigInt::operator-() const {
    return (*this) * -1;
}

const char BigInt::operator[](int n) const {
    string number = getNumber();
    return number[n];
}

// operatory logiczne
bool BigInt::operator==(const BigInt & b) const {
    return equals((*this), b);
}

bool BigInt::operator!=(const BigInt & b) const {
    return !equals((*this), b);
}

bool BigInt::operator>(const BigInt & b) const {
    return greater((*this), b);
}

bool BigInt::operator<(const BigInt & b) const {
    return less((*this), b);
}

bool BigInt::operator>=(const BigInt & b) const {
    return equals((*this), b)
           || greater((*this), b);
}

bool BigInt::operator<=(const BigInt & b) const {
    return equals((*this), b)
           || less((*this), b);

}

ostream & operator<<(ostream & os, const BigInt & b) {
    if (b.sign == true) os << '-' << b.number;
    else os << b.number;
    return os;
}

bool BigInt::equals(const BigInt & n1, const BigInt & n2) const {
    return n1.getNumber() == n2.getNumber() && n1.getSign() == n2.getSign();
}

bool BigInt::less(const BigInt & n1, const BigInt & n2) const {
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if (!sign1 && sign2)
        return false;

    else if (!sign1) // both +ve
    {
        if (n1.getNumber().length() < n2.getNumber().length())
            return true;
        if (n1.getNumber().length() > n2.getNumber().length())
            return false;
        return n1.getNumber() < n2.getNumber();
    }
    else // both -ve
    {
        if (n1.getNumber().length() > n2.getNumber().length())
            return true;
        if (n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare(n2.getNumber()) > 0; // greater with -ve sign is LESS
    }
}

bool BigInt::greater(const BigInt & n1, const BigInt & n2) const {
    return !equals(n1, n2) && !less(n1, n2);
}






