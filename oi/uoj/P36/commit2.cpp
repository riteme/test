#include <cstring>

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SMAX 63

typedef unsigned long long uint64;
typedef long double float128;

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

    sort(X, X + SMAX, greater<uint64>());
}

inline uint64 select(uint64 state) {
    uint64 sum = 0;
    for (int i = 0; i < m; i++) {
        if ((state >> i) & 1) {
            sum ^= X[i];
        }
    }

    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    initialize();
    
    float128 answer = 0.0L;
    for (uint64 s = 0; s < (1 << m); s++) {
        uint64 ret = select(s);
        uint64 result = ret;
        for (int i = 1; i < k; i++) {
            result *= ret;
        }

        answer += static_cast<float128>(result) / (1 << m);
    }

    cout.precision(20);
    cout << answer << endl;

    return 0;
}
