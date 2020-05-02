#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct vec {
    int x, y;

    bool operator==(const vec &z) const {
        return x == z.x && y == z.y;
    }
};

namespace std {
    template <>
    struct hash<vec> {
        size_t operator()(const vec &z) const {
            static hash<int> H;
            return H(z.x) ^ H(z.y);
        }
    };
}

int n, m;
vec p[NMAX + 10];
int id[NMAX + 10];
int seq[NMAX + 10];

int bit[NMAX + 10];

void modify(int x, int v) {
    for ( ; x <= n; x += x & -x)
        bit[x] = max(bit[x], v);
}

int query(int x) {
    int r = 0;
    for ( ; x; x -= x & -x)
        r = max(r, bit[x]);
    return r;
}

int A[NMAX + 10], B[NMAX + 10];

void initialize() {
    unordered_map<vec, int> tb;

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
        tb[p[i]] = 1;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", id + i);
        vec t = {p[id[i]].y, p[id[i]].x};
        if (!tb.count(t)) {
            tb[t] = -1;
            p[++n] = t;
        }
    }

    for (int i = 1; i <= n; i++)
        seq[i] = i;

    sort(seq + 1, seq + n + 1, [](int i, int j) {
        return p[i].y < p[j].y || (p[i].y == p[j].y && p[i].x < p[j].x);
    });

    for (int i = 1, j; i <= n; i = j) {
        for (j = i; j <= n && p[seq[i]].y == p[seq[j]].y; j++) ;

        for (int k = i; k < j; k++) {
            int x = seq[k];
            int v = query(p[x].x - 1);
            if (tb[p[x]] < 0)
                tb[p[x]] = -(v + 1);
            else
                tb[p[x]] = v + 1;
        }

        for (int k = i; k < j; k++) {
            int x = seq[k];
            int v = tb[p[x]];
            if (v >= 0)
                modify(p[x].x, v);
        }
    }

    for (int i = 1; i <= m; i++) {
        int j = id[i];
        vec q0 = p[j];
        vec q1 = {q0.y, q0.x};
        A[i] = abs(tb[q0]) - 1;
        B[i] = abs(tb[q1]) - 1;
    }
}

int z[32], msk[32], idx[32], cnt;
bool sel[NMAX + 10];

int main() {
    initialize();

    int t = 0;
    for (int i = 1; i <= m; i++)
        t ^= A[i];

    for (int i = 1; i <= m; i++) {
        int v = B[i] ^ A[i];
        idx[cnt] = i;
        int mask = 1 << cnt;
        for (int j = 0; j < 31; j++)
        if ((v >> j) & 1) {
            if (z[j] && ((v >> j) & 1)) {
                v ^= z[j];
                mask ^= msk[j];
            } else {
                z[j] = v;
                msk[j] = mask;
                cnt++;
                break;
            }
        }
    }

    int mask = 0;
    for (int j = 0; j < 31; j++)
    if (z[j] && ((t >> j) & 1)) {
        t ^= z[j];
        mask ^= msk[j];
    }

    if (t) {
        puts("impossible");
    } else {
        for (int j = 0; j < 31; j++)
        if ((mask >> j) & 1)
            sel[idx[j]] = true;

        for (int i = 1; i <= m; i++)
            putchar(sel[i] ? '1' : '0');
        puts("");
    }

    return 0;
}