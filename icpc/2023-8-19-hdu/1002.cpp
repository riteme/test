#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 10000;

int n;
char s[NMAX + 10], t[NMAX + 10];

void solve() {
    scanf("%d%s%s", &n, s, t);
    int sc = 0, tc = 0;
    for (int i = 0; i < n; i++) {
        sc += s[i] - '0';
        tc += t[i] - '0';
    }
    int c = max(0, sc + tc - n);
    int m = sc + tc - 2 * c;
    for (int i = 0; i < m; i++) {
        putchar('1');
    }
    for (int i = m; i < n; i++) {
        putchar('0');
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
