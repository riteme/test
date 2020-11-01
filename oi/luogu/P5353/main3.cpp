#include <cctype>
#include <cstdio>
#include <cstring>

#include <random>
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
constexpr int HMAX = NMAX | 1;

using u32 = unsigned int;
using u64 = unsigned long long;
using vi = vector<int>;

inline u64 mrand64() {
    static random_device rd;
    static u64 x = rd();
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

u64 wt[HMAX + 1];

void hash_init() {
    for (int i = 0; i <= HMAX; i++)
        wt[i] = mrand64();
}

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
    u64 *w;

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
        idx = new int[n];
        type = new bool[n];
        mark = new bool[n];
        w = new u64[n];

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
        for (auto j = G[sa[i]].rbegin(); j != G[sa[i]].rend(); j++)
        if (type[*j] == STYPE)
            sa[--cur[s[*j]]] = *j;
    }

    void _scan1(int x) {
        for (auto i = G[x].rbegin(); i != G[x].rend(); i++) {
            int v = *i;
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

    void _scan2(int x, int u, int t, int d, u64 w0, Solver &z) {
        for (int v : G[x]) if ((t >> type[v]) & 1) {
            auto w1 = w0 ^ ~(wt[d] ^ wt[HMAX - s[v]]);
            _scan2(v, u, ~(int) type[v], d + 1, w1, z);
        }
        if (x != u && mark[x]) {
            w[x] = w0;
            z[idx[u]].push_back(idx[x]);
        }
    }

    void scan2(Solver &z) {
        w[0] = ~wt[0] ^ wt[HMAX - (s[0] + 1)];
        for (int i = 0; i < n; i++)
        if (mark[i])
            _scan2(i, i, 0b01, 1, ~(wt[0] ^ wt[HMAX - s[i]]), z);
    }

    void rename(Solver &z) {
        u64 last;
        for (int i = 0; i < n; i++) {
            int x = sa[i];
            if (!mark[x]) continue;
            if (w[x] != last) pcnt++;
            z.s[idx[x]] = pcnt - 1;
            last = w[x];
        }
        z.m = pcnt;
    }

    void fast_solve() {
        for (int i = 0; i < n; i++)
            sa[s[i]] = i;
    }

    void reindex(Solver &z) {
        for (int i = 0; i < n; i++)
        if (mark[i])
            cur[idx[i]] = i;
        memcpy(idx, cur, sizeof(int) * z.n);
    }

    void scan3(Solver &z) {
        for (int i = z.n - 1; i >= 0; i--)
            sa[--cur[s[idx[z.sa[i]]]]] = idx[z.sa[i]];
    }

    void solve() {
        init();
        reset(); scan1(); induce();
        Solver z(mcnt);
        scan2(z); rename(z);
        pcnt == mcnt ?
            z.fast_solve() :
            z.solve();
        reindex(z);
        reset(); scan3(z); induce();
    }
};

char s[NMAX + 10];
int main() {
    hash_init();

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
