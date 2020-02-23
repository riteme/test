#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

typedef long long i64;

int n;
int p[NMAX + 10];

void scan(int v) {
    int cnt;
    scanf("%d", &cnt);
    for (int i = 0; i < cnt; i++) {
        int x;
        scanf("%d", &x);
        n = max(n, x);
        p[x] = v;
    }
}

int another(int s, int t) {
    if (s != 1 && t != 1)
        return 1;
    if (s != 2 && t != 2)
        return 2;
    return 3;
}

i64 solve(int i, int s, int t) {
    if (p[i] != s && p[i] != t)
        return -1;
    if (i == 1)
        return s == p[i] ? 0 : 1;
    if (p[i] == s)
        return solve(i - 1, s, another(s, t));
    i64 ret = solve(i - 1, another(s, t), t);
    if (ret >= 0)
        return (1LL << (i - 1)) + ret;
    return -1;
}

int main() {
    scan(1);
    scan(2);
    scan(3);
    i64 ans = solve(n, 1, 3);
    if (ans < 0) puts("No");
    else printf("%lld\n", (1LL << n) - 1 - ans);
    return 0;
}
