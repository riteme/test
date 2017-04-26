#pragma GCC optimize(3)
#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define SIGMA 26
#define MOD 1000000007

typedef long long i64;

class ACAutomaton {
 public:
    ACAutomaton() : n(1) {
        memset(trans, 0, sizeof(trans));
        memset(fail, 0, sizeof(fail));
        memset(match, 0, sizeof(match));
        fail[1] = 1;
    }

    void insert(const char *s) {
        int cur = 1;

        for (size_t p = 0; s[p]; p++) {
            int c = s[p] - 'a';

            if (!trans[cur][c])
                trans[cur][c] = ++n;

            cur = trans[cur][c];
        }

        match[cur] = true;
    }

    void build_fail() {
        queue<int> q;

        for (int c = 0; c < SIGMA; c++) {
            int v = trans[1][c];

            if (v) {
                q.push(v);
                fail[v] = 1;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int c = 0; c < SIGMA; c++) {
                int v = trans[u][c];
                
                if (!v)
                    continue;

                int x = u;
                do {
                    x = fail[x];

                    if (trans[x][c]) {
                        x = trans[x][c];
                        break;
                    }
                } while (x != 1);

                fail[v] = x;
                q.push(v);
            }
        }

        for (int i = 1; i <= n; i++) {
            if (match[i])
                continue;

            int x = i;
            do {
                x = fail[x];

                if (match[x]) {
                    match[i] = true;
                    break;
                }
            } while (x != 1);
        }
    }

    int run(int x, const char *s, bool &flag) {
        assert(!match[x]);

        for (size_t i = 0; !flag && s[i]; i++) {
            int c = s[i] - 'a';

            if (trans[x][c])
                x = trans[x][c];
            else {
                int y = x;
                do {
                    y = fail[y];

                    if (trans[y][c]) {
                        y = trans[y][c];
                        break;
                    }
                } while (y != 1);
                
                x = y;
            }

            if (match[x])
                flag = true;
        }

        return x;
    }
    
    int n;
    int trans[NMAX + 10][SIGMA];
    int fail[NMAX + 10];
    bool match[NMAX + 10];
};

struct Matrix {
    Matrix(int _n) : n(_n) {
        memset(mat, 0, sizeof(mat));
    }

    void identity() {
        for (int i = 1; i <= n; i++) {
            mat[i][i] = 1;
        }
    }

    Matrix &operator*=(const Matrix &b) {
        i64 c[NMAX + 10][NMAX + 10];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                register i64 s = 0;
                for (register int k = 1; k <= n; k++) {
                    s = (s + mat[i][k] * b.mat[k][j]) % MOD;
                }

                c[i][j] = s;
            }
        }

        memcpy(mat, c, sizeof(c));
        return *this;
    }

    i64 *operator[](const int i) {
        return mat[i];
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%lld ", mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    int n;
    i64 mat[NMAX + 10][NMAX + 10];
};

inline void quick_pow(Matrix &a, int b, Matrix &r) {
    r.identity();

    while (b) {
        if (b & 1)
            r *= a;
        a *= a;
        b >>= 1;
    }
}

static int n, m, L;
static char basic[NMAX + 10][NMAX + 10];
static int len[NMAX + 10];
static char forbid[NMAX + 10];
static ACAutomaton aut;

void initialize() {
    scanf("%d%d%d", &n, &m, &L);

    for (int i = 1; i <= n; i++) {
        scanf("%s", basic[i]);
        len[i] = strlen(basic[i]);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%s", forbid);
        aut.insert(forbid);
    }

    aut.build_fail();
}

static i64 f[NMAX + 10][NMAX + 10];

i64 solve1() {
    f[0][1] = 1;
    for (int i = 0; i < L; i++) {
        for (int j = 1; j <= aut.n; j++) {
            if (aut.match[j] || f[i][j] == 0)
                 continue;

            for (int k = 1; k <= n; k++) {
                if (i + len[k] > L)
                    continue;

                bool flag = false;
                int x = aut.run(j, basic[k], flag);

                if (!flag) {
                    f[i + len[k]][x] = (f[i + len[k]][x] + f[i][j]) % MOD;
                    // printf("%d, %d -> %d, %d (%lld, via %s)\n",
                    //        i, j, i + len[k], x, f[i][j], basic[k]);
                }
            }
        }
    }

    i64 answer = 0;
    for (int i = 1; i <= aut.n; i++) {
        answer = (answer + f[L][i]) % MOD;
    }

    return answer;
}

i64 solve2() {
    int l = aut.n;
    Matrix T(l * 2);

    for (int i = 1; i <= l; i++) {
        T[i + l][i] = 1;
    }

    for (int j = 1; j <= l; j++) {
        if (aut.match[j])
            continue;

        for (int i = 1; i <= n; i++) {
            bool flag = false;
            int x = aut.run(j, basic[i], flag);

            if (flag)
                continue;

            if (len[i] == 1)
                T[x][j]++;
            else if (len[i] == 2)
                T[x][j + l]++;
        }
    }

    // T.print();

    Matrix R(l * 2);
    quick_pow(T, L, R);

    i64 ret = 0;
    for (int i = 1; i <= l; i++) {
        ret = (ret + R[i][1]) % MOD;
    }

    return ret;
}

int main() {
#ifdef NDEBUG
    freopen("sorcery.in", "r", stdin);
    freopen("sorcery.out", "w", stdout);
#endif
    initialize();
    printf("%lld\n", L <= 100 ? solve1() : solve2());

    return 0;
}
