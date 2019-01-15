#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define QMAX 2000000
#define MOD 1000000007

struct Solver {
    enum CommandType {
        MODIFY = 0, QUERY = 1
    };

    struct Command {
        int type, x, y, v;

        bool operator<(const Command &z) const {
            return x < z.x ||
                   (x == z.x && type < z.type);
        }
    };

    Solver() : cnt(0), pos(0) {
        memset(bit, 0, sizeof(bit));
    }

    int cnt, pos;
    Command seq[QMAX + 10];
    int *ans[QMAX + 10], bit[NMAX + 10];

    void bit_modify(int x, int v) {
        for (; x <= NMAX; x += x & -x)
            bit[x] += v;
    }

    int bit_query(int x) {
        int ret = 0;
        for (; x; x -= x & -x)
            ret += bit[x];
        return ret;
    }

    void modify(int x1, int x2, int y1, int y2, int v) {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        // printf("x1 = %d, x2 = %d, y1 = %d, y2 = %d (+%d)\n", x1, x2, y1, y2, v);
        seq[cnt++] = {MODIFY, x1, y1, v};
        seq[cnt++] = {MODIFY, x1, y2 + 1, -v};
        seq[cnt++] = {MODIFY, x2 + 1, y1, -v};
        seq[cnt++] = {MODIFY, x2 + 1, y2 + 1, v};
    }

    void query(int x, int y, int *ptr) {
        seq[cnt++] = {QUERY, x, y, pos};
        ans[pos++] = ptr;
    }

    void solve() {
        memset(bit, 0, sizeof(bit));
        sort(seq, seq + cnt);
        // for (int i = 0; i < cnt; i++) {
        //     if (seq[i].type == MODIFY) continue;
        //     for (int j = 0; j < cnt; j++) {
        //         if (seq[j].type == MODIFY && seq[j].x <= seq[i].x && seq[j].y <= seq[i].y) {
        //             if (seq[i].x == 5 && seq[i].y == 4)
        //                 printf("%d, %d, %d\n", seq[j].x, seq[j].y, seq[j].v);
        //             *ans[seq[i].v] += seq[j].v;
        //         }
        //     }
        // }
        for (int i = 0; i < cnt; i++) {
            Command op = seq[i];
            switch (op.type) {
                case MODIFY:
                    bit_modify(op.y, op.v);
                break;
                case QUERY:
                    *ans[op.v] += bit_query(op.y);
                break;
            }
        }
    }
};

static int n, D, cur, d, ud;
static vector<int> G[NMAX + 10];
static int dep[NMAX + 10], in[NMAX + 10], out[NMAX + 10];
static int rnk[NMAX + 10], fa[NMAX + 10];
static i64 pw[NMAX + 10];
static deque<int> cnt[NMAX + 10];
static Solver sol1, sol2;

// 1: number of nodes within d steps; 2: periphery only
static int up1[NMAX + 10], dw1[NMAX + 10], up2[NMAX + 10], dw2[NMAX + 10];
static i64 prod[NMAX + 10];

void dfs(int x, int f) {
    in[x] = ++cur;
    rnk[x] = 1;
    for (int v : G[x]) {
        if (v == f) continue;
        dep[v] = dep[x] + 1;
        fa[v] = x;
        dfs(v, x);
        rnk[x] = max(rnk[x], rnk[v] + 1);
    }
    out[x] = cur;
}

void dp(int x, int f) {
    int u = 0;
    for (int v : G[x])
        if (v != f && rnk[v] > rnk[u]) u = v;
    if (u) {
        dp(u, x);
        cnt[x] = move(cnt[u]);
        dw1[x] = dw1[u];
    }

    cnt[x].push_front(1);
    dw1[x]++;
    if (cnt[x].size() > d + 1)
        dw1[x] -= cnt[x][d + 1];
    if (cnt[x].size() >= d + 1)
        dw2[x] = cnt[x][d];
    if (cnt[x].size() > ud + 1)
        cnt[x].pop_back();

    sol1.query(in[x], dep[x], up1 + x);
    sol2.query(in[x], dep[x], up2 + x);
    sol1.modify(in[x], out[x], dep[x] + 1, dep[x] + ud, 1);
    sol2.modify(in[x], out[x], dep[x] + ud, dep[x] + ud, 1);
    for (int v : G[x]) {
        if (v == u || v == f) continue;
        dp(v, x);
        for (int i = 0; i < min(ud - 1, static_cast<int>(cnt[v].size())); i++) {
            int td = dep[x] + ud - i - 1;
            sol1.modify(in[x], out[x], dep[x] + 1, td, cnt[v][i]);
            sol1.modify(in[v], out[v], dep[x] + 1, td, cnt[x][i + 1] - cnt[v][i]);
            sol2.modify(in[x], out[x], td, td, cnt[v][i]);
            sol2.modify(in[v], out[v], td, td, cnt[x][i + 1] - cnt[v][i]);
        }
    }

    for (int v : G[x]) {
        if (v == u || v == f) continue;
        for (int i = 0; i < cnt[v].size(); i++) {
            if (i < d) dw1[x] += cnt[v][i];
            if (i == d - 1) {
                prod[x] = (prod[x] + (pw[dw2[x]] - 1) * (pw[cnt[v][i]] - 1)) % MOD;
                dw2[x] += cnt[v][i];
            }
            cnt[x][i + 1] += cnt[v][i];
        }
    }
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &D);
    d = D / 2;
    ud = D - d;

    dep[1] = 1;
    dfs(1, 0);

    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * 2 % MOD;
}

int main() {
    initialize();

    // for (int i = 1; i <= n; i++)
    //     printf("%d: [%d, %d]\n", i, in[i], out[i]);

    if (D == 1) {
        printf("%d\n", n - 1);
        return 0;
    }

    dp(1, 0);
    sol1.solve();
    sol2.solve();

    // printf("d = %d, ud = %d\n", d, ud);
    // puts("i: dw1, dw2, up1, up2");
    // for (int i = 1; i <= n; i++)
    //     printf("%d: %3d, %3d, %3d, %3d\n", i, dw1[i], dw2[i], up1[i], up2[i]);

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        if (D & 1) {
            if (i == 1) continue;
            int m = dw1[i] + up1[i] - dw2[i] - up2[i];
            int a = dw2[i];
            int b = up2[i];
            if (a && b)
                ans = (ans + pw[m] * (pw[a] - 1) % MOD * (pw[b] - 1)) % MOD;
        } else {
            prod[i] = (prod[i] + (pw[dw2[i]] - 1) * (pw[up2[i]] - 1)) % MOD;
            int m = dw1[i] + up1[i] - dw2[i] - up2[i];
            ans = (ans + pw[m] * prod[i]) % MOD;
        }
    }

    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
