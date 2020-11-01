#include <cctype>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int BUFSIZE = 65536;
char _buf[BUFSIZE];
int _pos = BUFSIZE;

char _getc() {
    if (_pos == BUFSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

template <>
void read(char *&s) {
    char c;
    do c = _getc(); while (!isalnum(c));
    do {
        *(s++) = c;
        c = _getc();
    } while (isalnum(c));
}

constexpr int NMAX = 2000000;

using u32 = unsigned int;
using u64 = unsigned long long;
constexpr u32 MOD1 = 1000000007;
constexpr u32 MOD2 = 998244353;
constexpr u32 BASE = 19260817;
struct hash_t {
    hash_t() = default;
    hash_t(u32 v) : x(v), y(v) {}
    hash_t(u32 u, u32 v) : x(u), y(v) {}
    u32 x = 0, y = 0;
    hash_t append(u64 v) {
        u32 x0 = (x * BASE + v) % MOD1;
        u32 y0 = (y * BASE + v) % MOD2;
        return {x0, y0};
    }
    bool operator!=(const hash_t &z) const {
        return x != z.x || y != z.y;
    }
};

constexpr int PREALLOC = 2;
template <typename T>
struct vec {
    T *a = (T*) malloc(sizeof(T) * PREALLOC);
    int s = 0, c = PREALLOC;
    ~vec() { /* TODO */ }

    void push_back(T v) {
        if (s == c) {
            c += c >> 1;  // 1.5x scaling
            a = (T*) realloc(a, sizeof(T) * c);
        }
        a[s++] = v;
    }

    int size() { return s; }
    int *begin() { return a; }
    int *end() { return a + s; }
    T &operator[](int i) { return a[i]; }
};

using vi = vec<int>;
constexpr bool STYPE = 1;
constexpr bool LTYPE = 0;
int cur[NMAX + 10];
struct Solver {
    // input
    vi *G;
    int n, m, *s, *sa;

    // auxiliary
    int mcnt, pcnt, *cnt, *idx;
    bool *type, *mark;
    hash_t *w;

    Solver(int _n)
        : n(_n), m(0), mcnt(0), pcnt(0) {
        s = new int[n];
        sa = new int[n];
        G = new vi[n];
        s[0] = 0;
    }
    ~Solver() { /* TODO */ }
    vi &operator[](int i) { return G[i]; }

    void init() {
        //fprintf(stderr, "n=%d, m=%d\n", n, m);
        idx = new int[n];
        type = new bool[n];
        mark = new bool[n];
        w = new hash_t[n];

        cnt = new int[m];
        memset(cnt, 0, sizeof(int) * m);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    }

    void reset() {
        memset(sa, -1, sizeof(int) * n);
        memcpy(cur, cnt, sizeof(int) * m);
    }

    void induce() {
        cur[0] = 0;
        memcpy(cur + 1, cnt, sizeof(int) * (m - 1));
        for (int i = 0; i < n; i++) if (sa[i] >= 0)
        for (int j : G[sa[i]]) if (type[j] == LTYPE)
            sa[cur[s[j]]++] = j;

        // we must clear all S-buckets except the sentinel character,
        // since there may be some S edges below marked nodes.
        // UPD: not meaningful, since the S-bucket for the lexicographical
        // maximum character must be empty.
        //for (int i = 1; i < m; i++)
        //    memset(sa + cur[i], -1, sizeof(int) * (cnt[i] - cur[i]));

        memcpy(cur, cnt, sizeof(int) * m);
        for (int i = n - 1; i >= 0; i--) if (sa[i] >= 0)
        for (int j = G[sa[i]].size(); j; j--) {
            int v = G[sa[i]][j - 1];
            if (type[v] == STYPE)
                sa[--cur[s[v]]] = v;
        }
    }

    void _scan1(int x) {
        for (int i = G[x].size(); i; i--) {
            int v = G[x][i - 1];
            type[v] = (s[v] == s[x] && type[x]) || (s[v] < s[x]);
            if (type[v] == LTYPE)
                mark[x] = 1;
            _scan1(v);
        }
        mark[x] &= type[x] == STYPE;
        if (mark[x]) {
            if (x) idx[x] = mcnt++;
            sa[--cur[s[x]]] = x;
        }
    }

    void scan1() {
        memset(mark, 0, n);
        type[0] = STYPE;
        mark[0] = 1;
        idx[mcnt++] = 0;
        _scan1(0);
    }

    void _scan2(int x, int u, int t, hash_t w0, Solver &z) {
        for (int v : G[x]) if ((t >> type[v]) & 1) {
            auto w1 = w0.append(s[v] + 1);
            _scan2(v, u, ~(int) type[v], w1, z);
        }
        if (x != u && mark[x]) {
            w[x] = w0;
            z[idx[u]].push_back(idx[x]);
        }
    }

    void scan2(Solver &z) {
        w[0] = hash_t(s[0] + 1);
        for (int i = 0; i < n; i++)
        if (mark[i])
            _scan2(i, i, 0b01, hash_t(s[i] + 1), z);
    }

    void rename(Solver &z) {
        hash_t last;
        cur[0] = 0;
        for (int j = 0; j < m; j++)
        for (int i = cur[j]; i < cnt[j]; i++) {
            int x = sa[i];
            if (!mark[x]) continue;
            if (w[x] != last) pcnt++;
            z.s[idx[x]] = pcnt - 1;
            last = w[x];
        }
        z.m = pcnt;
    }

    void reindex() {
        for (int i = 0; i < n; i++)
        if (mark[i])
            cur[idx[i]] = i;
        memcpy(idx, cur, sizeof(int) * mcnt);
    }

    void scan3(Solver &z) {
        for (int i = z.n - 1; i >= 0; i--)
            sa[--cur[s[idx[z.sa[i]]]]] = idx[z.sa[i]];
    }

    void fast_solve() {
        for (int i = 0; i < n; i++)
            sa[s[i]] = i;
    }

    void solve() {
        init();
        reset(); scan1(); induce();
        Solver z(mcnt);
        scan2(z); rename(z); reindex();
        pcnt == mcnt ?
            z.fast_solve() :
            z.solve();
        reset(); scan3(z); induce();
    }
};

char s[NMAX + 10];
int main() {
    int n;
    read(n);
    Solver z(n + 1);
    z.m = 256;
    z[0].push_back(1);
    for (int v = 2; v <= n; v++) {
        int u;
        read(u);
        z[u].push_back(v);
    }
    char *t = s + 1;
    read(t);
    for (int i = 1; i <= n; i++) {
        z.s[i] = s[i];
    }
    z.solve();
    for (int i = 1; i <= n; i++) {
        printf("%d ", z.sa[i]);
    }
    puts("");
    return 0;
}
