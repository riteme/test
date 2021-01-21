#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using u64 = unsigned long long;

constexpr int NMAX = 100000;
constexpr int SMAX = 1000000;
constexpr u64 BASE = 0x19260817;

u64 h(char c) {
    return c ? 0x1926 : 0;
}

u64 pw[SMAX + 10];

struct str {
    int n;
    vector<u64> suf;
    vector<char> a;

    void init(const char *s) {
        n = strlen(s);
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = s[i] - '0';
        }

        init_hash();
    }

    void init_hash() {
        suf.resize(n + 1);
        suf[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            suf[i] = BASE * suf[i + 1] + h(a[i]);
        }
    }

    char &operator[](int i) {
        return a[i];
    }

    u64 hash(int l, int r) {
        if (r >= n)
            r = n - 1;
        if (r < l)
            return 0;
        return suf[l] - suf[r + 1] * pw[r - l + 1];
    }
};

int n;
char buf[SMAX + 10];
str t, v;
str s[NMAX + 10];

int main() {
    pw[0] = 1;
    for (int i = 1; i <= SMAX; i++) {
        pw[i] = pw[i - 1] * BASE;
    }

    t.n = SMAX;
    t.a.resize(SMAX);
    for (int i = 0; i < SMAX; i++) {
        t[i] = 0;
    }

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        s[i].init(buf);
        for (int j = 0; j < s[i].n; j++) {
            t[j] ^= s[i][j];
        }
    }

    t.init_hash();

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        v = s[i];
        for (int j = 0; j < s[i].n; j++) {
            v[j] ^= t[j];
        }
        v.init_hash();

        for (int j = 1; j < s[i].n; j++) {
            u64 h1 = t.hash(0, j - 1);
            u64 h2 = s[i].hash(j, 2 * j - 1);
            u64 h3 = v.hash(j, v.n - 1) + pw[v.n - j] * t.hash(v.n, SMAX);
            u64 h4 = s[i].hash(2 * j, SMAX);
            //printf("i=%d, j=%d, [%llx,%llx], [%llx,%llx]\n", i, j, h1, h2, h3, h4);

            if (h1 == h2 && h3 == h4)
                ans++;
        }
    }

    printf("%d\n", ans);

    return 0;
}
