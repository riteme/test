#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 300000;

int n, m, cnt;
i64 a[NMAX + 10], b[NMAX + 10];
vector<int> G[NMAX + 10];
vector<int> T[NMAX + 10];

int dfn[NMAX + 10], low[NMAX + 10], now;
int ed[NMAX + 10], pa[NMAX + 10];

void link(int u, int v) {
    T[u].push_back(v);
    T[v].push_back(u);
}

void build(int x, int p) {
    dfn[x] = low[x] = ++now;
    for (int v : G[x]) {
        if (v == p) {
            p = 0;
            continue;
        }
        if (dfn[v]) {
            ed[v] = x, low[x] = min(low[x], dfn[v]);
            continue;
        }
        pa[v] = x;
        build(v, x);
        if (low[v] > dfn[x])
            link(v, x);
        else if (low[v] == dfn[x]) {
            cnt++;
            int u = n + cnt;
            for (v = ed[x]; v != x; v = pa[v]) {
                link(u, v);
            }
            link(u, x);
        } else
            low[x] = min(low[x], low[v]);
    }
}

i64 A[NMAX + 10], B[NMAX + 10];

void dfs(int x, int p) {
    A[x] = a[x];
    B[x] = b[x];

    for (int v : T[x]) if (v != p) {
        pa[v] = x;
        dfs(v, x);
        A[x] += A[v];
        B[x] += B[v];
    }
}

i64 maxw = -1;
vector<pair<int, int>> ans;

void update(i64 w, int u, int v) {
    // printf("%d-%d: %lld\n", u, v, w);
    if (w > maxw) {
        maxw = w;
        ans.clear();
    }

    if (w >= maxw)
        ans.push_back({u, v});
}

int p[NMAX + 10];
i64 c[NMAX + 10], d[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", a + i, b + i);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    build(1, 0);
    pa[1] = 0;
    dfs(1, 0);

    for (int v = 1; v <= n; v++) {
        int u = pa[v];
        if (!u || u > n)
            continue;

        i64 a1 = A[1] - A[v];
        i64 b1 = B[1] - B[v];
        i64 a2 = A[v];
        i64 b2 = B[v];
        i64 w = 2 * (a1 * b2 + a2 * b1);
        update(w, u, v);
    }

    for (int x = n + 1; x <= n + cnt; x++) {
        int L = T[x].size();
        int H = (L - 1) / 2;

        for (int i = 0; i < L; i++) {
            int y = T[x][i];
            p[i] = y;
            if (pa[y] == x) {
                c[i] = A[y];
                d[i] = B[y];
            } else {
                c[i] = A[1] - A[x];
                d[i] = B[1] - B[x];
            }
        }

        i64 base = 0;
        if (L % 2 == 0) {
            for (int i = 0; i + H + 1 < L; i++) {
                int j = i + H + 1;
                base += c[i] * d[j] + c[j] * d[i];
            }
        }

        c[L] = 0;
        d[L] = 0;
        for (int i = L - 1; i >= 0; i--) {
            c[i] += c[i + 1];
            d[i] += d[i + 1];
        }

        auto wrap = [L](int x) {
            while (x < 0) {
                x += L;
            }
            while (x >= L) {
                x -= L;
            }
            return x;
        };

        auto ran = [wrap](i64 *z, int s, int t) {
            s = wrap(s);
            t = wrap(t);

            if (s <= t)
                return z[s] - z[t + 1];
            else
                return z[0] - z[t + 1] + z[s];
        };

        auto get = [wrap](i64 *z, i64 i) {
            i = wrap(i);
            return z[i] - z[i + 1];
        };

        if (H > 0) {
            i64 sum = 0;
            for (int i = 1; i <= H; i++) {
                sum += ran(c, i - H, 0) * get(d, i) + ran(d, i - H, 0) * get(c, i);
            }

            for (int i = 0; i < L; i++) {
                int j = wrap(i + 1);
                update(base + 2 * sum, p[i], p[j]);

                int k = wrap(j + 1);
                sum -= ran(c, j - H, i) * get(d, j) + ran(d, j - H, i) * get(c, j);
                sum += get(c, j) * ran(d, k, j + H) + get(d, j) * ran(c, k, j + H);
            }
        }
    }

    for (auto &e : ans) {
        if (e.first > e.second)
            swap(e.first, e.second);
    }
    sort(ans.begin(), ans.end());

    printf("%zu\n", ans.size());
    for (auto &e : ans) {
        printf("%d %d\n", e.first, e.second);
    }

    return 0;
}