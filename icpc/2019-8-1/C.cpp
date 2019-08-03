#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define HASHMOD 233333
#define HASHSIZE 1000000

static struct HashTable {
    int head[HASHMOD];
    int key[HASHSIZE + 10], val[HASHSIZE + 10], nxt[HASHSIZE + 10], cnt;

    void clear() {
        cnt = 0;
        memset(head, 0, sizeof(head));
    }

    int operator[](const int k) {
        for (int i = head[k % HASHMOD]; i; i = nxt[i])
            if (key[i] == k) return val[i];
        return 0;
    }

    void add(int k, int v) {
        int p = k % HASHMOD;
        nxt[++cnt] = head[p];
        key[cnt] = k;
        val[cnt] = v;
        head[p] = cnt;
    }
} tb;

typedef long long i64;

inline int qpow(i64 a, int k, int P) {
    i64 r = 1;
    for ( ; k; k >>= 1, a = a * a % P)
        if (k & 1) r = r * a % P;
    return r;
}

inline int inv(int x, int P) {
    return qpow(x, P - 2, P);
}

inline void chkmin(int &a, int b) {
    if (b < a) a = b;
}

static i64 n;
static int x0, a, b, p, q, S;

inline int query(int v) {
    i64 t = i64(v) * a % p;
    int r = p;
    for (int j = 1; j <= S; j++, t = t * a % p) {
        int x = tb[t];
        if (x) chkmin(r, x * S - j);
    }
    return r < p && r < n ? r : -1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%d%d%d%d%d", &n, &x0, &a, &b, &p, &q);
        tb.clear();
        S = int(sqrt(p / q)) + 1;
        i64 pw = qpow(a, S, p);
        for (int i = 1, t = pw; i * S <= p + S - 1; i++, t = pw * t % p)
            if (!tb[t]) tb.add(t, i);
        while (q--) {
            int v;
            scanf("%d", &v);
            if (a == 0) {
                if (v == x0) puts("0");
                else if (v == b) puts(n > 1 ? "1" : "-1");
                else puts("-1");
            } else if (a == 1) {
                if (!b) puts(v == x0 ? "0" : "-1");
                else {
                    int i = (i64(v - x0) * inv(b, p) % p + p) % p;
                    printf("%d\n", i < n ? i : -1);
                }
            } else {
                i64 t = (i64(b) * inv(a - 1, p) % p + p) % p;
                i64 c = (x0 + t) % p;
                i64 d = (v + t) % p;
                if (!c) puts(d ? "0" : "-1");
                else printf("%d\n", query(d * inv(c, p) % p));
            }
        }
    }
    return 0;
}
