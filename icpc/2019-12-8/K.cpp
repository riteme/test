#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Node {
    Node(int _key)
        : w(rand()), key(_key), sum(1),
          lch(NULL), rch(NULL) {}

    int w, key, sum;
    Node *lch, *rch;

    void update() {
        sum = 1 + (lch ? lch->sum : 0) + (rch ? rch->sum : 0);
    }
};

Node *lrot(Node *x) {
    Node *y = x->lch;
    x->lch = y->rch;
    y->rch = x;
    x->update();
    y->update();
    return y;
}

Node *rrot(Node *x) {
    Node *y = x->rch;
    x->rch = y->lch;
    y->lch = x;
    x->update();
    y->update();
    return y;
}

Node *insert(Node *x, int key) {
    if (!x) return new Node(key);
    if (key < x->key) {
        x->lch = insert(x->lch, key);
        if (x->lch->w < x->w) return lrot(x);
    } else {
        x->rch = insert(x->rch, key);
        if (x->rch->w < x->w) return rrot(x);
    }
    x->update();
    return x;
}

int _sum(Node *x) {
    return x ? x->sum : 0;
}

int query(Node *x, int r) {
    if (!x) return 0;
    if (x->key <= r)
        return _sum(x->lch) + 1 + query(x->rch, r);
    return query(x->lch, r);
}

typedef unordered_map<int, Node*> Bucket;

static int n, K;
static int a[NMAX + 10];
static vector<int> G[NMAX + 10];
static int dep[NMAX + 10], size[NMAX + 10];
static Bucket *mp[NMAX + 10];

void dfs(int x) {
    size[x] = 1;
    for (int v : G[x]) {
        dep[v] = dep[x] + 1;
        dfs(v);
        size[x] += size[v];
    }
}

static i64 ans;

void calc(Node *x, Node *y, int dx) {
    if (!x) return;
    ans += query(y, K + 2 * dx - x->key);
    calc(x->lch, y, dx);
    calc(x->rch, y, dx);
}

Node *add(Node *x, Node *y) {
    if (!x) return y;
    y = insert(y, x->key);
    y = add(x->lch, y);
    y = add(x->rch, y);
    return y;
}

void solve(int x) {
    int u = 0;
    for (int v : G[x])
        if (size[v] > size[u]) u = v;
    if (u) {
        solve(u);
        mp[x] = mp[u];
    } else
        mp[x] = new Bucket;
    for (int v : G[x]) if (v != u) {
        solve(v);
        for (auto &e : *mp[v]) {
            int av = e.first;
            int t = 2 * a[x] - av;
            if (mp[x]->count(t))
                calc(e.second, (*mp[x])[t], dep[x]);
        }
        for (auto &e : *mp[v]) {
            int av = e.first;
            (*mp[x])[av] = add(e.second, (*mp[x])[av]);
        }
    }
    auto &tr = (*mp[x])[a[x]];
    tr = insert(tr, dep[x]);
}

int main() {
    srand(19260817);
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int v = 2; v <= n; v++) {
        int u;
        scanf("%d", &u);
        G[u].push_back(v);
    }
    dfs(1);
    solve(1);
    printf("%lld\n", ans * 2);
    return 0;
}
