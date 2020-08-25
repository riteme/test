#pragma comment(linker, "/STACK:102400000,102400000")

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000

struct Node {
    Node(int L, int R)
        : l(L), r(R), sum(0), sum0(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    int l, r;
    int sum, sum0;
    Node *lch, *rch;

    int rsum() {
        return sum + (r - l + 1) * sum0;
    }

    void fetch() {
        if (!lch)
            return;
        sum = lch->rsum() + rch->rsum();
    }

    void commit() {
        if (!lch)
            return;
        if (sum0) {
            sum = rsum();
            lch->sum0 += sum0;
            rch->sum0 += sum0;
            sum0 = 0;
        }
    }

    void reset() {
        sum = sum0 = 0;
        if (lch) {
            lch->reset();
            rch->reset();
        }
    }

    void modify(int L, int R, int v) {
        if (L <= l && r <= R)
            sum0 += v;
        else {
            commit();
            int m = (l + r) / 2;
            if (L <= m)
                lch->modify(L, R, v);
            if (R > m)
                rch->modify(L, R, v);
            fetch();
        }
    }

    int query(int L, int R) {
        if (L <= l && r <= R)
            return rsum();

        commit();
        int ret = 0;
        int m = (l + r) / 2;
        if (L <= m)
            ret += lch->query(L, R);
        if (R > m)
            ret += rch->query(L, R);

        return ret;
    }

    int query(int x) {
        return query(x, x);
    }
};

int n, K;
vector<int> G[NMAX + 10];
bool mark[NMAX + 10];
int m, a[NMAX + 10];
Node *tl = new Node(1, NMAX), *tr = new Node(1, NMAX);
int dist[NMAX + 10], pa[NMAX + 10];

template <typename TCallback>
void scan(int x, int p, const TCallback &fn) {
    fn(x);
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (mark[v] || v == p)
            continue;
        scan(v, x, fn);
    }
}

int top;
void add_left(int x) {
    if (dist[x] - dist[top] > K)
        return;

    tl->modify(dist[top], dist[top] + K - (dist[x] - dist[top]), +1);
}

void add_right(int x) {
    if (dist[x] - dist[top] > K)
        return;

    tr->modify(dist[top] - K + (dist[x] - dist[top]), dist[top], +1);
}

void del_left(int x) {
    if (dist[x] - dist[top] > K)
        return;

    tl->modify(dist[top], dist[top] + K - (dist[x] - dist[top]), -1);
}

void del_right(int x) {
    if (dist[x] - dist[top] > K)
        return;

    tr->modify(dist[top] - K + (dist[x] - dist[top]), dist[top], -1);
}

int solve() {
    tl->reset();
    tr->reset();
    memset(mark + 1, 0, n);
    for (int i = 1; i <= m; i++) {
        mark[a[i]] = true;
    }

    if (m - 1 <= K)
        return n;

    int i = 1, j = K + 1;
    int s = K / 2;
    for (int k = i; k <= i + s; k++) {
        top = a[k];
        scan(a[k], 0, add_left);
    }
    for (int k = i + s + 1; k <= j; k++) {
        top = a[k];
        scan(a[k], 0, add_right);
    }

    int ans = tr->query(i) + tl->query(j);
    for (i = 1; i < m - K; i++, j++) {
        top = a[i];
        scan(a[i], 0, del_left);
        top = a[j + 1];
        scan(a[j + 1], 0, add_right);
        top = a[i + s + 1];
        scan(top, 0, del_right);
        scan(top, 0, add_left);
        int ret = tr->query(i + 1) + tl->query(j + 1);
        //printf("i=%d, ret=%d\n", i, ret);
        ans = max(ans, ret);
    }

    return ans;
}

void dfs(int x) {
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == pa[x])
            continue;
        dist[v] = dist[x] + 1;
        pa[v] = x;
        dfs(v);
    }
}

void _main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    pa[1] = 0;
    dist[1] = 0;
    dfs(1);
    int u = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[u])
            u = i;
    }
    pa[u] = 0;
    dist[u] = 0;
    dfs(u);
    int v = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[v])
            v = i;
    }

    int x = v;
    m = 0;
    while (x != u) {
        a[++m] = x;
        x = pa[x];
    }
    a[++m] = u;

    dist[v] = 1;
    pa[v] = 0;
    dfs(v);
    int ans = solve();
    printf("%d\n", n - ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
