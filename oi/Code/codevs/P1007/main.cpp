#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    double k;
    cin >> k;

    double n = 1.0;
    double sum = 0.0;

    do {
        sum += 1.0 / n;
        n += 1.0;
    } while (sum <= k);  // do ... while

    cout << int(n) - 1;

    return 0;
}  // function main
