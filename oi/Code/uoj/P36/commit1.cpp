#include <cstring>

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SMAX 63

typedef long long int64;
typedef unsigned long long uint64;
typedef long double float128;

static int n, k;
static uint64 f[SMAX + 10][2];

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> k;

    for (int p = 0; p < SMAX; p++) {
        f[p][0] = 1;
    }

    for (int i = 0; i < n; i++) {
        int64 x;
        cin >> x;

        for (int p = 0; p < SMAX; p++) {
            int bit = (x >> p) & 1;

            if (bit) {
                uint64 t0 = f[p][0];
                uint64 t1 = f[p][1];
                f[p][0] += t1;
                f[p][1] += t0;
            } else {
                f[p][0] <<= 1;
                f[p][1] <<= 1;
            }
        }
    }

    float128 answer = 0.0;
    float128 tpow = 1.0L;
    for (int p = 0; p < SMAX; p++) {
        answer += static_cast<float128>(f[p][1]) /
                  (f[p][0] + f[p][1]) * tpow;
        tpow *= 2.0L;
    }

    cout << answer << endl;

    return 0;
}
