#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

inline void _getc(char &c) {
    static unsigned short pos;
    static char buf[USHRT_MAX + 1];
    if (!pos) fread(buf, 1, USHRT_MAX + 1, stdin);
    c = buf[pos++];
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

#define MMAX 10000
#define NMAX 500

struct Item {
    int i, j = 0, v = 0;
    Item *nxt = NULL;

    bool operator<(const Item &b) const {
        return v < b.v;
    }
};

static int m, n[MMAX + 10], cnt, last[MMAX + 10], f[MMAX + 10];
static Item A[MMAX * (NMAX + 1) + 10], *_buc[2][NMAX + 10][2];
static auto buc = _buc[1];  // Support negative index

inline void submit(Item *a, Item *b) {
    int v = max(a->v, b->v) + a->i + b->i;
    f[a->i] ^= v;
    if (a->i != b->i) f[b->i] ^= v;
}

int main() {
#ifdef USE_FILE_IO
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
#endif

    read(m);
    for (int i = 1; i <= m; i++) {
        read(n[i]);
        A[cnt].i = i;
        for (int j = 1; j <= n[i]; j++) {
            A[cnt + j].i = i;
            read(A[cnt + j].v);
        }
        cnt += n[i] + 1;
    }
    sort(A, A + cnt);
    for (int t = 0; t < cnt; t++) {
        int i = A[t].i;
        if (last[i] == ((n[i] + 1) >> 1)) f[i] = A[t].v + 2 * i;
        A[t].j = last[i]++;
    }

    for (int i = -NMAX; i <= NMAX; i++) {
        buc[i][0] = new Item;
        buc[i][1] = new Item;
    }
    for (auto u = A + 0; u != A + cnt; u++) {
        int p[2] = { u->j - ((n[u->i] + (n[u->i] & 1)) >> 1), u->j - (n[u->i] >> 1) };
        last[u->i] = u->j;
        for (int b = 0; b < 2; b++) for (auto px = buc[p[b]][b], x = px->nxt; x; x = x->nxt) {
            if (last[x->i] > x->j) px->nxt = x->nxt;
            else submit(u, x), px = x;
        }
        auto q = buc[-p[!(n[u->i] & 1)]][n[u->i] & 1];
        u->nxt = q->nxt;
        q->nxt = u;
    }

    for (int i = 1; i <= m; i++) printf("%d\n", f[i]);
    return 0;
}
