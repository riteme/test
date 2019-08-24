#include <cmath>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

bool IsPrime(int n);
int ComputeExpression(unsigned expression, const vector<int> &numbers);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    vector<int> numbers;

    int n;
    cin >> n;

    numbers.resize(n);
    for (int i = 0; i < n; i++) { cin >> numbers[i]; }  // for

    unsigned int end = 0U;
    for (int i = 0; i < n; i++) { end = (end << 1) + 1U; }  // for

    int cnt = 0;

    // k < n
    for (unsigned i = 1U; i <= end; i++) {
        if (IsPrime(ComputeExpression(i, numbers))) { cnt++; }
    }  // for

    cout << cnt << endl;

    return 0;
}  // function main

bool IsPrime(int n) {
    if (n < 2) { return false; }
    if (n >= 5 && !((n + 1) % 6 == 0 || (n - 1) % 6 == 0)) { return false; }

    int upBound = sqrt(n);
    for (int i = 2; i <= upBound; i++) {
        if (n % i == 0) { return false; }
    }  // for

    return true;
}

int ComputeExpression(unsigned expression, const vector<int> &numbers) {
    bitset<sizeof(expression) * 8> bitExpression(expression);
    int sum = 0;

    for (int i = numbers.size() - 1; i >= 0; i--) {
        if (bitExpression.test(i)) { sum += numbers[i]; }
    }  // for

    return sum;
}
