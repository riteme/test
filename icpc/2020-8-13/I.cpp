#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000000
#define MOD1 998244353
#define MOD2 14630479
#define BASE 19260817

typedef long long i64;

struct num {
    num() : x(0), y(0) {}
    num(i64 _x, i64 _y) : x(_x), y(_y) {
        if (x > MOD1)
            x -= MOD1;
        else if (x < 0)
            x += MOD1;
        if (y > MOD2)
            y -= MOD2;
        else if (y < 0)
            y += MOD2;
    }

    i64 x, y;

    num operator+(const num &z) const {
        return num(x + z.x, y + z.y);
    }

    num operator-(const num &z) const {
        return num(x - z.x, y - z.y);
    }

    num operator*(const num &z) const {
        return num(x * z.x % MOD1, y * z.y % MOD2);
    }

    num operator*(i64 k) const {
        return num(x * k % MOD1, y * k % MOD2);
    }

    bool operator==(const num &z) const {
        return x == z.x && y == z.y;
    }
};

num pw[NMAX + 10];
int n;
int nxt[NMAX + 10];
char s[NMAX + 10];
num h[NMAX + 10];

num H(int l, int r) {
    return h[r] - h[l - 1] * pw[r - l + 1];
}

void _main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * BASE + num(s[i], s[i]);
    }

    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j > 0 && s[j + 1] != s[i]) {
            j = nxt[j];
        }
        if (s[j + 1] == s[i])
            j++;
        nxt[i] = j;
    }

    for (int l = 1; l < n; l++) if (n % l == 0) {
        bool ok = true;
        for (int i = 2 * l; i <= n && ok; i += l)
            ok &= nxt[i] >= l || H(nxt[i] + 1, l) == H(i - l + 1, i - nxt[i]);

        if (ok) {
            puts("Yes");
            return;
        }
    }

    puts("No");
}

int main() {
    pw[0] = num(1, 1);
    for (int i = 1; i <= NMAX; i++) {
        pw[i] = pw[i - 1] * BASE;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
