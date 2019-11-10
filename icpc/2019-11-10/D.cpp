#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef unsigned long long u64;

int tb[100][100][100];

u64 solve(u64 n, u64 s, u64 K) {
    //fprintf(stderr, "n = %llu, s = %llu\n", n, s);
    if (n <= 2 * K) return tb[n][s][K];
    assert(0 <= s && s < n);
    u64 m = (n - s + K - 1) / K;
    assert(m >= 1);
    u64 ns = (s + m * K) % n;
    //fprintf(stderr, "m = %llu\n", m);
    u64 p = solve(n - m, ns, K);
    return (p < s ? p : p + (p - s) / (K - 1) + 1);
}

int main() {
    for (int K = 2; K <= 10; K++)
    for (int n = 1; n <= 20; n++)
    for (int s = 0; s < n; s++) {
        bool mark[n];
        memset(mark, 0, sizeof(mark));
        int j = s;
        mark[s] = true;
        for (int i = 0; i < n - 2; i++) {
            for (int c = 0; c < K; c++) {
                j = (j + 1) % n;
                while (mark[j]) j = (j + 1) % n;
            }
            mark[j] = true;
        }
        for (int i = 0; i < n; i++) if (!mark[i]) {
            tb[n][s][K] = i;
            break;
        }
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        u64 n, s, K;
        scanf("%llu%llu%llu", &n, &s, &K);
        if (K == 1) printf("%llu\n", s);
        else printf("%llu\n", solve(n, (s - 1 + K) % n, K) + 1);
    }
    return 0;
}
