#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

typedef unsigned DigitType;
typedef vector<DigitType> BigNumber;

DigitType ToDigit(const char c);
char ToChar(const DigitType d);

BigNumber ParseBigNumber(const string &data);
BigNumber ComputeMason(const DigitType &p);
BigNumber ComputeMason(const DigitType &p, int depth,
                       vector<unique_ptr<BigNumber>> &values);
void PrintBigNumber(const BigNumber &n);

void Multiply(const BigNumber &a, const BigNumber &b, BigNumber &output);
void Subtraction(const BigNumber &a, const DigitType &b, BigNumber &output);

int main() {
    ios::sync_with_stdio(false);

    DigitType p;
    cin >> p;

    BigNumber result = ComputeMason(p);

    PrintBigNumber(result);
    // PrintBigNumber(p);

    return 0;
}  // function main

BigNumber ParseBigNumber(const string &data) {
    BigNumber result;

    for (auto beg = data.rbegin(); beg != data.rend(); beg++) {
        result.push_back(ToDigit(*beg));
    }  // for

    return result;
}

BigNumber ComputeMason(const DigitType &p) {
    BigNumber result;
    vector<unique_ptr<BigNumber>> values;

    result = ComputeMason(p, 0, values);
    Subtraction(result, 1, result);

    return result;
}

BigNumber ComputeMason(const DigitType &p, int depth,
                       vector<unique_ptr<BigNumber>> &values) {}

void PrintBigNumber(const BigNumber &n) {
    for (auto beg = n.rbegin(); beg != n.rend(); beg++) {
        cout << ToChar(*beg);
    }  // for

    cout << endl;
}

DigitType ToDigit(const char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }  // switch to c

    return 10;
}

char ToChar(const DigitType d) {
    switch (d) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
    }  // switch to c

    return '?';
}
