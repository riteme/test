#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static vector<bool> PrimeTable;

#define MAX_NUMBER 20000

void GeneratePrimeTable(unsigned max);
unsigned FloorPrime(unsigned n);
unsigned FindMaxFactor(unsigned n);

int main(/*int argc, char *argv[]*/) {
    cout.sync_with_stdio(false);

    unsigned n, maxFactor = 1, maxNum = 1;
    cin >> n;

    GeneratePrimeTable(MAX_NUMBER);

    for (unsigned i = 1; i <= n; i++) {
        unsigned current;
        cin >> current;

        auto factor = FindMaxFactor(current);

        if (factor > maxFactor) {
            maxFactor = factor;
            maxNum = current;
        }
    }  // for

    cout << maxNum << endl;

    return 0;
}  // function main

void GeneratePrimeTable(unsigned max) {
    PrimeTable.resize(max + 1);

    std::fill(PrimeTable.begin(), PrimeTable.end(), true);

    // PrimeTable[0] = false;
    // PrimeTable[1] = false;

    for (unsigned i = 2; i <= max; i++) {
        if (PrimeTable[i]) {
            for (unsigned j = i + i; j <= max; j += i) { PrimeTable[j] = false; }  // for
        }
    }  // for
}

unsigned FloorPrime(unsigned n) {
    while (!PrimeTable[n]) { n--; }  // while
    return n;
}

unsigned FindMaxFactor(unsigned n) {
    if (PrimeTable[n]) { return n; }

    unsigned factor = FloorPrime(n - 1);

    while (n % factor != 0) { factor = FloorPrime(factor - 1); }  // while

    return factor;
}
