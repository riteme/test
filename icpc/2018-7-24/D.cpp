#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

inline i64 calc(int n, int m) {
    i64 ans = 1LL * (n / 2) * (m + 1);
    if (n & 1) ans += (m + 1) / 2;
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        i64 n, m;
        scanf("%lld%lld", &n, &m);
        printf("%lld\n", min(calc(n, m), calc(m, n)));
    }

    return 0;
}
