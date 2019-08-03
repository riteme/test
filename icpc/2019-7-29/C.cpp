#include <cstdio>
#include <cctype>
#include <cstring>

#include <tr1/unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::tr1;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

inline void read(char *s) {
    do _getc(s[0]); while (!isdigit(s[0]));
    do {
        s++;
        _getc(s[0]);
    } while (isdigit(s[0]));
}

#define NMAX 50000

typedef long long i64;
typedef unsigned long long u64;

int exgcd(int x, int y, int &n, int &m) {
    if (!y) {
        n = 1;
        m = 0;
        return x;
    }
    int n0, m0, r = exgcd(y, x % y, n0, m0);
    n = m0;
    m = n0 - x / y * m0;
    return r;
}

inline int inv(int x, int p) {
    if (p == 1) return 0;
    int n, m;
    exgcd(x, p, n, m);
    return n;
}

int n, p, q, K;
i64 M2, M5, M;
char d[NMAX + 10];
vector<int> G[NMAX + 10];
i64 t2[NMAX + 10], t5[NMAX + 10], t[NMAX + 10], ti[NMAX + 10];

void initialize() {
    //scanf("%d%lld%s", &n, &M, d + 1);
    read(n); read(M); read(d + 1);
    for (int i = 1; i <= n; i++) {
        d[i] -= '0';
        G[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        //scanf("%d%d", &u, &v);
        read(u); read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (p = 0, M2 = 1; M % (M2 * 2) == 0; M2 *= 2, p++) ;
    for (q = 0, M5 = 1; M % (M5 * 5) == 0; M5 *= 5, q++) ;
    K = max(p - 1, q - 1);
    M /= M2 * M5;
    int iv = inv(10, M);
    for (int i = 1; i <= n; i++) {
        t2[i] = t2[i - 1] * 10 % M2;
        t5[i] = t5[i - 1] * 10 % M5;
        t[i] = t[i - 1] * 10 % M;
        ti[i] = ti[i - 1] * iv % M;
    }
}

bool used[NMAX + 10];
int size[NMAX + 10];

void calc_size(int x, int fa = 0) {
    size[x] = 1;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == fa || used[v]) continue;
        calc_size(v, x);
        size[x] += size[v];
    }
}

int median(int x, int std) {
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (!used[v] && 2 * size[v] > std && size[v] < size[x])
            return median(v, std);
    }
    return x;
}

int len[NMAX + 10], c[NMAX + 10], cnt;
i64 A2[NMAX + 10], A5[NMAX + 10], A[NMAX + 10];
i64 B2[NMAX + 10], B5[NMAX + 10], B[NMAX + 10];

void scan(int x, int fa) {
    c[++cnt] = x;
    len[x] = len[fa] + 1;
    A2[x] = (A2[fa] + d[x] * t2[len[x]]) % M2;
    A5[x] = (A5[fa] + d[x] * t5[len[x]]) % M5;
    A[x] = (A[fa] + d[x] * t[len[x]]) % M;
    B2[x] = (B2[fa] * 10 + d[x]) % M2;
    B5[x] = (B5[fa] * 10 + d[x]) % M5;
    B[x] = (B[fa] * 10 + d[x]) % M;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (used[v] || v == fa) continue;
        scan(v, x);
    }
}

template <typename T, typename TKey>
inline i64 query(const T &mp, const TKey &key) {
    typename T::const_iterator it = mp.find(key);
    if (it == mp.end()) return 0;
    return it->second;
}

inline u64 key(u64 k, u64 v2, u64 v5, u64 v) {
    return v ^ (v2 << 17) ^ (v5 << 34) ^ (k << 47);
}

i64 solve(int x) {
    calc_size(x);
    x = median(x, size[x]);
    A2[x] = d[x] % M2, A5[x] = d[x] % M5, A[x] = d[x] % M;
    len[x] = B2[x] = B5[x] = B[x] = 0;
    unordered_map<u64, int> Q0, R0;
    unordered_map<int, int> Q1, R1;
    i64 ret = d[x] % (M * M2 * M5) == 0;
    for (int _i = 0; _i < G[x].size(); _i++) {
        int v = G[x][_i];
        if (used[v]) continue;
        cnt = 0;
        scan(v, x);
        for (int i = 1; i <= cnt; i++) {
            v = c[i];
            i64 val = (M - ti[len[v]] * B[v] % M) % M;
            ret += A2[v] == 0 && A5[v] == 0 && A[v] == 0;
            ret += (d[x] * t2[len[v]] + B2[v]) % M2 == 0 &&
                   (d[x] * t5[len[v]] + B5[v]) % M5 == 0 &&
                   (d[x] * t[len[v]] + B[v]) % M == 0;
            if (len[v] <= K)
                ret += query(Q0, key(len[v], (M2 - B2[v]) % M2, (M5 - B5[v]) % M5, val));
            else if (B2[v] == 0 && B5[v] == 0)
                ret += query(Q1, val);
            for (int k = 0; k <= K; k++)
                ret += query(R0, key(k, A2[v] * t2[k] % M2, A5[v] * t5[k] % M5, A[v]));
            ret += query(R1, A[v]);
        }
        for (int i = 1; i <= cnt; i++) {
            int v = c[i];
            i64 val = (M - ti[len[v]] * B[v] % M) % M;
            for (int k = 0; k <= K; k++)
                Q0[key(k, A2[v] * t2[k] % M2, A5[v] * t5[k] % M5, A[v])]++;
            Q1[A[v]]++;
            if (len[v] <= K)
                R0[key(len[v], (M2 - B2[v]) % M2, (M5 - B5[v]) % M5, val)]++;
            else if (B2[v] == 0 && B5[v] == 0) R1[val]++;
        }
    }

    used[x] = true;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (!used[v]) ret += solve(v);
    }
    return ret;
}

int main() {
    int T;
    //scanf("%d", &T);
    read(T);
    t2[0] = t5[0] = t[0] = ti[0] = 1;
    while (T--) {
        initialize();
        memset(used + 1, 0, n);
        printf("%lld\n", solve(1));
    }
    return 0;
}
