#include <cstring>

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SMAX 64

typedef unsigned long long uint64;

static int n, k;
static uint64 seq[NMAX + 10];
static int m;
static uint64 X[SMAX + 10];

static void initialize() {
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> seq[i];

        uint64 x = seq[i];
        for (int p = SMAX - 1; p >= 0; p--) {
            if ((x >> p) & 1) {
                if (X[p]) {
                    x ^= X[p];
                } else {
                    m++;
                    X[p] = x;
                    break;
                }
            }
        }
    }
}

static bool test(int p) {
    for (int i = 0; i < SMAX; i++) {
        if ((X[i] >> p) & 1)
            return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    uint64 answer = 0;
    for (int i = 1; i < SMAX; i++) {
        if (test(i))
            answer += 1L << (i - 1);
    }

    cout << answer << (test(0) ? ".5" : "") << endl;
    
    return 0;
}
