#define NDEBUG

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define QMAX 10
#define VEGEMAX NMAX * QMAX
#define HEAPSIZE (NMAX * 2 + 10)

#ifndef NDEBUG
#define DEBUG(msg, ...) printf(msg, __VA_ARGS__);
#else 
#define DEBUG(...)
#endif

typedef long long i64;

// Pairing Heap
struct Node {
    int x, w;
    int head, nxt;
};

static int _pos;
static Node hp[HEAPSIZE];

inline int mkheap(int x, int w) {
    int i = ++_pos;
    hp[i] = {x, w, 0, 0};
    return i;
}

inline int meld(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (hp[y].w > hp[x].w) swap(x, y);
    
    hp[y].nxt = hp[x].head;
    hp[x].head = y;
    return x;
}

inline int extract(int x) {
    static int stk[HEAPSIZE], tail, last, t;
    tail = last = 0;
    for (int y = hp[x].head; y; y = t) {
        t = hp[y].nxt;
        hp[y].nxt = 0;
        if (last) {
            stk[tail++] = meld(last, y);
            last = 0;
        } else last = y;
    }

    hp[x].head = 0;
    if (last) stk[tail++] = last;
    for (int i = 1; i < tail; i++)
        stk[i] = meld(stk[i - 1], stk[i]);
    return stk[tail - 1];
}

static int n, m, Q, q;
static int A[NMAX + 10], S[NMAX + 10], C[NMAX + 10], X[NMAX + 10], R[NMAX + 10];
static int used[NMAX + 10], tm[NMAX + 10], sorted[VEGEMAX + 10];
static i64 ans[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &Q, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d%d", A + i, S + i, C + i, X + i);
    for (int i = 1; i <= q; i++) {
        scanf("%d", R + i);
        m = max(m, R[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (static_cast<i64>(m) * X[i] >= C[i]) tm[i] = (C[i] - 1) / X[i] + 1;
        else tm[i] = m;
        sorted[i] = i;
    }
    sort(sorted + 1, sorted + n + 1,
         [](const int x, const int y) {
             return tm[x] > tm[y];
         });
}

inline int cnt(int x, int y) {
    return C[x] - (y - 1) * X[x] - used[x];
}

inline int w(int x) {
    return x > n ? A[x - n] + S[x - n] : A[x];
}

int main() {
    initialize();

    i64 &ret = ans[m];
    int H = 0, p = 1;
    vector<int> rec;
    for (int i = m; i >= 1; i--) {
        while (tm[sorted[p]] == i) { // p > n, sorted[p] = 0
            int x = sorted[p++];
            H = meld(H, mkheap(x, A[x] + S[x]));
        }

        for (int x : rec)
            H = meld(H, mkheap(x, A[x]));
        rec.clear();

        for (int j = 0; j < Q && H; j++) {
            DEBUG("%d: %d\n", hp[H].x, hp[H].w);
            ret += hp[H].w;
            int x = hp[H].x;
            used[x]++;

            if (cnt(x, i) == 0) {
                H = extract(H);
                if (X[x]) rec.push_back(x);
            } else if (hp[H].w > A[x]) {
                H = extract(H);
                if (cnt(x, i)) H = meld(H, mkheap(x, A[x]));
                else if (X[x]) rec.push_back(x);
            }
        }
    }

    p = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i]) continue;
        sorted[p++] = n + i;
        for (int j = 0; j < used[i] - 1; j++)
            sorted[p++] = i;
    }
    sort(sorted, sorted + p,
         [](const int x, const int y) {
             return w(x) > w(y);
         });

    DEBUG("p = %d\n", p);
    for (int i = m - 1; i >= 1; i--) {
        ans[i] = ans[i + 1];
        while (p > Q * i) {
            DEBUG("%d: %d\n", sorted[p - 1], w(sorted[p - 1]));
            ans[i] -= w(sorted[--p]);
        }
    }

    for (int i = 1; i <= q; i++) {
        printf("%lld\n", ans[R[i]]);
    }

    return 0;
}
