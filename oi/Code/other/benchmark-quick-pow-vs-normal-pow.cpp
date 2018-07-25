#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

typedef unsigned long long ntype;

auto mypow(ntype n, ntype exp) -> ntype {
    ntype result = n;
    for (ntype i = 1; i < exp; i++) { result *= n; }
    return result;
}

auto quick_pow(ntype n, ntype exp) -> ntype {
    if (exp == 1)
        return n;
    else if (exp & 1)
        return quick_pow(n, exp / 2) * quick_pow(n, exp / 2) * n;
    else
        return quick_pow(n, exp / 2) * quick_pow(n, exp / 2);
}

int main() {
    ios::sync_with_stdio(false);

    // cout << std::pow(2ULL, 63ULL) << '\n';
    // cout << mypow(2ULL, 63ULL) << '\n';
    cout << quick_pow(2ULL, 63ULL) << '\n';

    return 0;
}  // function main
