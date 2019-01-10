#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef unsigned long long i8;

inline i8 T(i8 n) {
    return ((i8(1) << (2*n)) - 1) / 3;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long _n, _k;
        scanf("%lld%lld", &_n, &_k);
        i8 n = _n, k = _k, a = n, m = 0;
        bool ok = false;
        while (true) {
            if (m > k || a < 0) break;
            if (a == n && k == 0) ok = true;
            else if (a < n && n >= 32) ok = true;
            else {
                i8 mt = T(n) - ((i8(1) << (n - a + 1)) - 1) * T(a);
                if (mt >= k) ok = true;
            }
            if (ok) {
                printf("YES %d\n", int(a));
                break;
            } else {
                if (a == n) m = 1;
                else m += (i8(1) << (n - a + 1)) - 1;
                if (a == 0) break;
                a--;
            }
        }
        if (!ok) puts("NO");
    }
    return 0;
}
