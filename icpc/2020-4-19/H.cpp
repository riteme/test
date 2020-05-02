#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);

        i64 c = ((n - 1) ^ (m - 1) ^ (k - 1)) & 1;
        i64 o = (n * m * k) & 1;
        i64 p = c == o;
        printf("%lld\n", n * m * k - p);
    }

    return 0;
}