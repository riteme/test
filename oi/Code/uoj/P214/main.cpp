#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 30
#define MOD 998244353

typedef long long i64;

inline i64 inv(i64 n) {
    return n == 1 ? 1 : (MOD - MOD / n) * inv(MOD % n) % MOD;
}

static int n, m, s;
static bool S[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10][NMAX + 10];
static int T[NMAX + 10];
static int C[NMAX * NMAX + 10][NMAX * NMAX + 10];
static char buf[NMAX + 10];

void initialize() {
    memset(S, 0, sizeof(S));
    memset(T, 0, sizeof(T));
    scanf("%d%d", &n, &m);

    s = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        s += strlen(buf);
        for (int j = 0; buf[j]; j++) {
            S[i][buf[j] - 'a'] = true;
        }
    }

    scanf("%s", buf);
    for (int i = 0; i < m; i++) {
        T[i] = buf[i] - 'a';
    }
}

inline bool check() {
    bool ret = false;
    for (int i = 0; i <= n - m; i++) {
        bool matched = true;
        for (int j = 0; j < m; j++) {
            if (!S[i + j][T[j]])
                matched = false;
        }

        ret |= matched;
    }

    return true;
}

inline void add(i64 &a, i64 b) {
    a += b % MOD;

    if (a >= MOD)
        a -= MOD;
    if (a < 0)
        a += MOD;
}

int main() {
    C[0][0] = 1;
    for (int i = 1; i <= NMAX * NMAX; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    int _t;
    scanf("%d", &_t);

    while (_t--) {
        initialize();

        if (!check()) {
            puts("-1");
            continue;
        }

        i64 ans = 0;
        for (int A = 0; A < (1 << (n - m + 1)); A++) {
            memset(marked, 0, sizeof(marked));
            bool flag = false;
            int c = 0;
            for (int i = 0; i <= n - m; i++) {
                if (!((A >> i) & 1))
                    continue;

                c++;
                for (int j = 0; j < m; j++) {
                    if (!S[i + j][T[j]])
                        flag = true;
                    marked[i + j][T[j]] = true;
                }
            }

            if (flag)
                continue;

            int k = 0;
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j < 26; j++) {
                    if (marked[i][j])
                        k++;
                }
            }

            for (int i = 1; i <= k; i++) {
                add(ans, ((i + c) & 1 ? -1 : 1) * s * inv(i) % MOD * C[k][i]);
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
