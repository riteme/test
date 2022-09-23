#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <queue>
#include <random>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 150000;
constexpr i64 MOD = 1000000007;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
constexpr int L = 0;
constexpr int R = 1;

struct Node {
    i64 wt;
    i64 key;
    int size, cnt;
    i64 sum, val;
    Node *lch, *rch;

    void fetch() {
        size = cnt;
        sum = val;
        if (lch) {
            size += lch->size;
            sum = (sum + lch->sum) % MOD;
        }
        if (rch) {
            size += rch->size;
            sum = (sum + rch->sum) % MOD;
        }
    }
} m[NMAX * 3 + 10];
int mcnt = 0;

Node *nalloc(i64 key, i64 val) {
    Node *p = m + mcnt;
    mcnt++;
    p->key = key;
    p->cnt = p->size = 1;
    p->val = p->sum = val % MOD;
    p->lch = p->rch = NULL;
    return p;
}

Node *lrot(Node *x) {
    Node *y = x->lch;
    x->lch = y->rch;
    y->rch = x;
    x->fetch();
    y->fetch();
    return y;
}

Node *rrot(Node *x) {
    Node *y = x->rch;
    x->rch = y->lch;
    y->lch = x;
    x->fetch();
    y->fetch();
    return y;
}

Node *insert(Node *x, i64 key, i64 val) {
    if (!x)
        return nalloc(key, val);

    if (key < x->key) {
        x->lch = insert(x->lch, key, val);
        if (x->lch->wt < x->wt)
            return lrot(x);
    } else if (key > x->key) {
        x->rch = insert(x->rch, key, val);
        if (x->rch->wt < x->wt)
            return rrot(x);
    } else {
        x->cnt += 1;
        x->val = (x->val + val) % MOD;
    }
    x->fetch();
    return x;
}

i64 qsum(Node *x, i64 key) {
    if (!x)
        return 0;
    if (key < x->key)
        return qsum(x->lch, key);
    return ((x->lch ? x->lch->sum : 0) + x->val + qsum(x->rch, key)) % MOD;
}

int qsize(Node *x, i64 key) {
    if (!x)
        return 0;
    if (key < x->key)
        return qsize(x->lch, key);
    return (x->lch ? x->lch->size : 0) + x->cnt + qsize(x->rch, key);
}

struct vec {
    i64 x, y;
    bool is_query;
};

bool cmp_x(const vec &a, const vec &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cmp_y(const vec &a, const vec &b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

struct Scanline {
    int n;
    vec p[NMAX * 3 + 10];

    void reset() {
        n = 0;
    }

    void add(i64 x, i64 y, bool is_query) {
        p[n++] = {x, y, is_query};
    }

    i64 eval() {
        i64 rax = 0;

        sort(p, p + n, cmp_x);
        i64 sum = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].is_query)
                rax = (rax + (cnt * (p[i].x % MOD) - sum)) % MOD;
            else {
                sum = (sum + p[i].x) % MOD;
                cnt += 1;
            }
        }

        mcnt = 0;
        Node *tr = NULL;
        for (int i = 0; i < n; i++) {
            i64 z = p[i].y - p[i].x;
            if (p[i].is_query) {
                i64 sum = qsum(tr, z - 1);
                i64 cnt = qsize(tr, z - 1);
                rax = (rax - (cnt * (p[i].x % MOD) - sum)) % MOD;
            } else
                tr = insert(tr, z, p[i].x);
        }

        sort(p, p + n, cmp_y);
        sum = cnt = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].is_query)
                rax = (rax + (cnt * (p[i].y % MOD) - sum)) % MOD;
            else {
                sum = (sum + p[i].y) % MOD;
                cnt += 1;
            }
        }

        mcnt = 0;
        tr = NULL;
        for (int i = 0; i < n; i++) {
            i64 z = p[i].x - p[i].y;
            if (p[i].is_query) {
                i64 sum = qsum(tr, z);
                i64 cnt = qsize(tr, z);
                rax = (rax - (cnt * (p[i].y % MOD) - sum)) % MOD;
            } else
                tr = insert(tr, z, p[i].y);
        }

        return -rax;
    }
} aha;

i64 w[NMAX + 10][3];
i64 f[NMAX + 10][2];

void shortest(i64 dist[][3], int l, int r, int sx, int sy) {
    for (int i = l; i <= r; i++)
    for (int j = 0; j < 3; j++) {
        dist[i][j] = INF;
    };
    dist[sx][sy] = w[sx][sy];

    struct State {
        i64 t;
        int x, y;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    priority_queue<State> q;
    q.push({dist[sx][sy], sx, sy});
    do {
        auto [t, x, y] = q.top();
        q.pop();
        if (t > dist[x][y])
            continue;

        auto add = [&q, &dist, l, r](int tx, int ty, i64 t) {
            if (tx < l || tx > r || ty < 0 || ty > 2)
                return;
            t += w[tx][ty];
            if (dist[tx][ty] > t) {
                dist[tx][ty] = t;
                q.push({t, tx, ty});
            }
        };

        add(x - 1, y, t);
        add(x + 1, y, t);
        add(x, y - 1, t);
        add(x, y + 1, t);

        if (x == l && y == 0)
            add(x, 2, t + f[l][L]);
        if (x == l && y == 2)
            add(x, 0, t + f[l][L]);
        if (x == r && y == 0)
            add(x, 2, t + f[r][R]);
        if (x == r && y == 2)
            add(x, 0, t + f[r][R]);
    } while (q.size());
}

int n;
i64 ans = 0;
i64 d[3][NMAX + 10][3];

void solve(int l, int r) {
    if (r < l)
        return;

    int m = (l + r) / 2;
    for (int i = 0; i < 3; i++) {
        shortest(d[i], l, r, m, i);
    }

    for (int i = 0; i < 3; i++)
    for (int x = l; x <= r; x++)
    for (int y = 0; y < 3; y++) {
        if (x == m && y < i)
            continue;
        ans = (ans + d[i][x][y]) % MOD;
    };

    aha.reset();
    i64 suml = 0, sumr = 0;
    i64 cntl = (m - l) * 3, cntr = (r - m) * 3;
    for (int x = l; x < m; x++)
    for (int y = 0; y < 3; y++) {
        suml = (suml + d[0][x][y]) % MOD;
        aha.add(d[1][x][y] - d[0][x][y], d[2][x][y] - d[0][x][y], false);
    };
    for (int x = m + 1; x <= r; x++)
    for (int y = 0; y < 3; y++) {
        sumr = (sumr + d[0][x][y]) % MOD;
        aha.add(
            (d[0][x][y] - w[m][0]) - (d[1][x][y] - w[m][1]),
            (d[0][x][y] - w[m][0]) - (d[2][x][y] - w[m][2]),
            true
        );
    };

    ans = (ans + suml * cntr) % MOD;
    ans = (ans + sumr * cntl) % MOD;
    ans = (ans - cntl * cntr % MOD * w[m][0]) % MOD;
    ans = (ans + aha.eval()) % MOD;

    solve(l, m - 1);
    solve(m + 1, r);
}

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    for (int i = 0; i < NMAX * 3 + 10; i++) {
        m[i].wt = gen();
    }

    int _;
    scanf("%d%d", &_, &n);
    for (int j = 0; j < 3; j++)
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &w[i][j]);
    };

    f[1][L] = w[1][1];
    for (int i = 2; i <= n; i++) {
        f[i][L] = min(f[i - 1][L] + w[i - 1][0] + w[i - 1][2], w[i][1]);
    }

    f[n][R] = w[n][1];
    for (int i = n - 1; i >= 1; i--) {
        f[i][R] = min(f[i + 1][R] + w[i + 1][0] + w[i + 1][2], w[i][1]);
    }

    solve(1, n);

    for (int i = 1; i <= n; i++)
    for (int j = 0; j < 3; j++) {
        ans = (ans - w[i][j]) % MOD;
    };;

    ans = ans * 2 % MOD;
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    // ans = 0;
    // for (int i = 1; i <= n; i++)
    // for (int j = 0; j < 3; j++) {
    //     shortest(d[0], 1, n, i, j);
    //     for (int i = 1; i <= n; i++)
    //     for (int j = 0; j < 3; j++) {
    //         ans = (ans + d[0][i][j]) % MOD;
    //     }
    // };
    // for (int i = 1; i <= n; i++)
    // for (int j = 0; j < 3; j++) {
    //     ans = (ans - w[i][j]) % MOD;
    // };
    // if (ans < 0)
    //     ans += MOD;
    // printf("std=%lld\n", ans);

    return 0;
}