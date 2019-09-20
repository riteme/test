#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 70000
#define MMAX 150000
#define EMAX 4000000

static struct Node {
    int id;
    int lch, rch;
    int x, y;
} e[EMAX + 10];
static int cnt;

static int rev[NMAX + 10];
int insert(int x, int p, int i, int xl, int xr) {
    if (!x) x = ++cnt;
    if (xl == xr) {
        rev[i] = x;
        e[x].id = i;
    } else {
        int m = (xl + xr) >> 1;
        if (p <= m) e[x].lch = insert(e[x].lch, p, i, xl, m);
        else e[x].rch = insert(e[x].rch, p, i, m + 1, xr);
    }
    return x;
}

int meld(int x, int y, int l, int r) {
    if (!x) return y;
    if (!y) return x;
    int z = ++cnt;
    e[z].x = x;
    e[z].y = y;
    if (l < r) {
        int m = (l + r) >> 1;
        e[z].lch = meld(e[x].lch, e[y].lch, l, m);
        e[z].rch = meld(e[x].rch, e[y].rch, m + 1, r);
    }
    return z;
}

#define L(x) (x << 1)
#define R(x) (L(x) | 1)

static int n, m, W, H;
static int rt[4 * NMAX + 10];

void set(int x, int i, int j, int k, int xl, int xr) {
    if (xl == xr) rt[x] = insert(rt[x], k, i, 1, n);
    else {
        int m = (xl + xr) >> 1;
        if (j <= m) set(L(x), i, j, k, xl, m);
        else set(R(x), i, j, k, m + 1, xr);
    }
}

void build(int x, int xl, int xr) {
    if (xl < xr) {
        int m = (xl + xr) >> 1;
        build(L(x), xl, m);
        build(R(x), m + 1, xr);
        rt[x] = meld(rt[L(x)], rt[R(x)], 1, n);
    }
}

static int tail, seq[NMAX + 10];
void scan(int x, int L, int R, int xl, int xr) {
    if (L <= xl && xr <= R) seq[tail++] = x;
    else {
        int m = (xl + xr) >> 1;
        if (L <= m) scan(e[x].lch, L, R, xl, m);
        if (R > m) scan(e[x].rch, L, R, m + 1, xr);
    }
}

void scan(int x, int L, int R, int D, int U, int xl, int xr) {
    if (L <= xl && xr <= R) scan(rt[x], D, U, 1, n);
    else {
        int m = (xl + xr) >> 1;
        if (L <= m) scan(L(x), L, R, D, U, xl, m);
        if (R > m) scan(R(x), L, R, D, U, m + 1, xr);
    }
}

struct State {
    int u, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

struct Rect {
    int t, L, R, D, U;
};

static vector<Rect> G[NMAX + 10];
static int dist[EMAX + 10];

void shortest() {
    memset(dist, 0x3f, sizeof(dist));
    dist[rev[1]] = 0;
    priority_queue<State> q;
    q.push({rev[1], 0});
    while (!q.empty()) {
        State s = q.top();
        q.pop();
        if (dist[s.u] < s.t) continue;
        int u = s.u;
        if (e[u].id) {
            for (auto &[t, L, R, D, U] : G[e[u].id]) {
                tail = 0;
                scan(1, L, R, D, U, 1, n);
                for (int i = 0; i < tail; i++) {
                    int v = seq[i];
                    if (dist[v] > dist[u] + t) {
                        dist[v] = dist[u] + t;
                        q.push({v, dist[v]});
                    }
                }
            }
        } else {
            auto push = [&q](int v, int t) {
                if (!v) return;
                if (dist[v] > t) {
                    dist[v] = t;
                    q.push({v, t});
                }
            };
            if (e[u].x) {
                push(e[u].x, s.t);
                push(e[u].y, s.t);
            } else {
                push(e[u].lch, s.t);
                push(e[u].rch, s.t);
            }
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &W, &H);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        set(1, i, x, y, 1, n);
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int u, t, L, R, D, U;
        scanf("%d%d%d%d%d%d", &u, &t, &L, &R, &D, &U);
        G[u].push_back({t, L, R, D, U});
    }
    shortest();
    for (int i = 2; i <= n; i++) printf("%d\n", dist[rev[i]]);
    return 0;
}
