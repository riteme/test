#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define CNT(x) __builtin_popcount(x)
#define LOGW 5
#define W (1 << LOGW)
#define MOD (W - 1)
#define NMAX 65536
#define MAXR 1565
#define LOGN 15
#define LEN (NMAX / W)

typedef unsigned int u32;
typedef long long i64;

struct Bits {
    Bits() : L(0), R(LEN), l(0), r(NMAX) {
        memset(w, 0, sizeof(w));
    }

    int L, R, l, r;
    struct {
        int L, R, l, r;
    } mem;
    u32 w[MAXR];

    int size() const {
        return R - L;
    }

    int count() const {
        if (L + 1 == R) {
            if (L >= MAXR) return 0;
            int len = r - l;
            u32 mask = len < W ? (1 << len) - 1 : -1;
            u32 bits = (w[L] >> (l & MOD)) & mask;
            return CNT(bits);
        }

        int ret = 0;
        for (int i = L; i < R && i < MAXR; i++)
            ret += CNT(w[i]);
        return ret;
    }

    void reset() {
        memset(w, 0, sizeof(w));
    }

    void reset_bounds() {
        L = l = 0;
        R = LEN;
        r = NMAX;
    }

    void set(int v) {
        int i = v >> LOGW, j = v & MOD;
        w[i] |= 1 << j;
    }

    bool test(int v) const {
        int i = v >> LOGW, j = v & MOD;
        return (w[i] >> j) & 1;
    }

    void to_left() {
        mem = {L, R, l, r};
        if (L + 1 < R)
            R = (L + R) >> 1;
        r = (l + r) >> 1;
    }

    void to_right() {
        mem = {L, R, l, r};
        if (L + 1 < R)
            L = (L + R) >> 1;
        l = (l + r) >> 1;
    }

    void back() {
        L = mem.L;
        R = mem.R;
        l = mem.l;
        r = mem.r;
    }

    Bits &operator&=(const Bits &z) {
        for (int i = 0; i < size() && L + i < MAXR && z.L + i < MAXR; i++)
            w[L + i] &= z.w[z.L + i];
        return *this;
    }

    Bits &operator|=(const Bits &z) {
        for (int i = 0; i < size() && L + i < MAXR && z.L + i < MAXR; i++)
            w[L + i] |= z.w[z.L + i];
        return *this;
    }
};

static int n, m, q;
static vector<int> G[NMAX + 10];
static Bits r[NMAX + 10];

static bool mark[NMAX + 10];
static int dfn[NMAX + 10], low[NMAX + 10], tim;
static int id[NMAX + 10], cnt;
static i64 sum;

void dfs(int x) {
    static int stk[NMAX + 10], t;
    static Bits used;

    dfn[x] = low[x] = ++tim;
    stk[++t] = x;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (!dfn[v])
            dfs(v);
        if (!mark[v])
            low[x] = min(low[x], low[v]);
    }

    if (low[x] == dfn[x]) {
        cnt++;
        //printf("cnt = %d\n", cnt);
        int u, t0 = t;
        do {
            u = stk[t--];
            mark[u] = true;
            id[u] = cnt;
            //printf("id[%d] = %d\n", u, cnt);
            r[x].set(u);
        } while (u != x);

        used.reset();
        for (int i = t + 1; i <= t0; i++) {
            u = stk[i];
            for (int j = 0; j < G[u].size(); j++) {
                int v = G[u][j];
                assert(mark[v]);
                if (id[u] != id[v] && !used.test(id[v])) {
                    r[x] |= r[v];
                    used.set(id[v]);
                }
            }
        }

        i64 s = r[x].count();
        sum += (t0 - t) * s;
        for (int i = t + 1; i <= t0; i++) if (stk[i] != x)
            r[stk[i]] = r[x];
    }
}

void reset_bounds() {
    for (int u = 1; u <= n; u++)
        r[u].reset_bounds();
}

void initialize() {
    //scanf("%d%d%d", &n, &m, &q);
    read(n); read(m); read(q);
    for (int i = 0; i < m; i++) {
        int u, v;
        //scanf("%d%d", &u, &v);
        read(u); read(v);
        G[u].push_back(v);
    }
    reset_bounds();
    for (int u = 1; u <= n; u++)
        if (!mark[u]) dfs(u);
}

void finalize() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        r[i].reset();
    }
    memset(mark, 0, sizeof(mark));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    cnt = tim = sum = 0;
}

int solve(i64 K) {
    int ret = 0;
    reset_bounds();
    for (int k = LOGN; K > 1 && k >= 0; k--) {
        i64 c = 0;
        for (int u = 1; u <= n; u++) {
            int b = (u >> k) & 1;
            if (b)
                r[u].to_right();
            else
                r[u].to_left();
            c += r[u].count();
            r[u].back();
        }
        //printf("[%d] c = %lld, K = %lld\n", k, c, K);
        if (c < K) {
            ret |= 1 << k;
            K -= c;
            for (int u = 1; u <= n; u++) {
                int b = (u >> k) & 1;
                if (b)
                    r[u].to_left();
                else
                    r[u].to_right();
            }
        } else {
            for (int u = 1; u <= n; u++) {
                int b = (u >> k) & 1;
                if (b)
                    r[u].to_right();
                else
                    r[u].to_left();
            }
        }
    }
    //assert(K == 1);
    return ret;
}


int main() {
    int T;
    //scanf("%d", &T);
    read(T);
    while (T--) {
        //auto t0 = high_resolution_clock::now();
        initialize();
        //auto t1 = high_resolution_clock::now();
        //printf("%.6lf\n", duration<double>(t1 - t0).count());

        //int p = 0;
        //static int tmp[1000];
        //for (int u = 1; u <= n; u++) for (int v = 1; v <= n; v++)
        //if (r[u].test(v)) tmp[p++] = u ^ v;
        //sort(tmp, tmp + sum);
        //for (int i = 0; i < sum; i++)
        //    printf("%d ", tmp[i]);
        //puts("");

        //t0 = high_resolution_clock::now();
        while(q--) {
            i64 K;
            //scanf("%lld", &K);
            read(K);
            //printf("sum = %lld\n", sum);
            //assert(K <= sum);
            if (q <= 2) printf("%d\n", solve(sum - K + 1));
        }
        //t1 = high_resolution_clock::now();
        //printf("%.6lf\n", duration<double>(t1 - t0).count());
        finalize();
    }
    return 0;
}
