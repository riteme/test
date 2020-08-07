#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 200000
#define MEMSIZE 1800000

struct Pair {
    int u, v;

    bool operator==(const Pair &z) const {
        return u == z.u && v == z.v;
    }
};

namespace std {
    template <>
    struct hash<Pair> {
        size_t operator()(const Pair &z) const {
            static hash<int> H;
            return H(z.u) ^ H(z.v);
        }
    };
}

int n, m;
vector<int> G[NMAX + 10], T[NMAX + 10];

bool marked[NMAX + 10];
int in[NMAX + 10], low[NMAX + 10], cur, cnt;
void bcc(int u, int f = 0) {
    static stack<Pair> stk;
    in[u] = low[u] = ++cur;
    for (int v : G[u]) {
        if (v == f) f = 0;
        else if (in[v]) low[u] = min(low[u], in[v]);
        else {
            stk.push(Pair{u, v});
            bcc(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u]) {
                T[u].push_back(v);
                T[v].push_back(u);
                stk.pop();
            } else if (low[v] >= in[u]) {
                cnt++;
                int linked = 0, p = n + cnt;
                auto add = [p, &linked](int x) {
                    if (!marked[x]) {
                        marked[x] = true;
                        T[p].push_back(x);
                        T[x].push_back(p);
                        linked++;
                    }
                };
                while (!stk.empty()) {
                    Pair x = stk.top();
                    stk.pop();
                    add(x.u);
                    add(x.v);
                    if (x.u == u && x.v == v)
                        break;
                }
                for (int v : T[p]) {
                    marked[v] = false;
                }
                if (linked == 0)
                    cnt--;
            }
        }
    }
}

struct Node {
    int sum;
    Node *lch, *rch;

    Node() {
        memset(this, 0, sizeof(Node));
    }
};

// Node mem[MEMSIZE];
// size_t mempos;
// Node *allocate() {
//     auto r = mem + mempos;
//     mempos++;
//     memset(r, 0, sizeof(Node));
//     return r;
// }

Node *single(int p, int xl, int xr) {
    // Node *x = allocate();
    Node *x = new Node;
    x->sum = 1;

    Node *y = x;
    while (xl < xr) {
        int mi = (xl + xr) / 2;
        // Node *z = allocate();
        Node *z = new Node;
        z->sum = 1;

        if (p <= mi) {
            y->lch = z;
            xr = mi;
        } else {
            y->rch = z;
            xl = mi + 1;
        }
        y = z;
    }

    return x;
}

Node *meld(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;
    x->sum += y->sum;  // assume disjoint
    x->lch = meld(x->lch, y->lch);
    x->rch = meld(x->rch, y->rch);
    delete y;
    return x;
}

void release(Node *x) {
    if (!x)
        return;
    release(x->lch);
    release(x->rch);
    delete x;
}

int maxp(Node *x, int xl, int xr) {  // present
    if (xl == xr)
        return xl;

    int mi = (xl + xr) / 2;
    if (x->rch)
        return maxp(x->rch, mi + 1, xr);
    return maxp(x->lch, xl, mi);
}

int maxnp(Node *x, int xl, int xr) {  // not present
    if (!x)
        return xr;

    int mi = (xl + xr) / 2;
    if (!x->rch || x->rch->sum < (xr - mi))
        return maxnp(x->rch, mi + 1, xr);
    return maxnp(x->lch, xl, mi);
}

unordered_map<Pair, Pair> ans;

Node *dfs(int u, int pa = 0) {
    Node *tr = NULL;
    for (int v : T[u]) if (v != pa) {
        auto t = dfs(v, u);
        tr = meld(tr, t);
    }

    tr = meld(tr, single(u, 1, n));
    if (pa && pa <= n && u <= n) {
        Pair key = {u, pa};
        if (key.u > key.v)
            swap(key.u, key.v);

        int mp = maxp(tr, 1, n);
        if (mp == n)
            mp = maxnp(tr, 1, n);
        ans[key] = {mp, mp + 1};
    }

    return tr;
}

Pair key[NMAX + 10];

void initialize() {
    // mempos = 0;
    scanf("%d%d", &n, &m);
    memset(marked + 1, 0, 2 * n);
    memset(in + 1, 0, sizeof(int) * 2 * n);
    memset(low + 1, 0, sizeof(int) * 2 * n);
    cur = cnt = 0;
    for (int i = 1; i <= 2 * n; i++) {
        G[i].clear();
        T[i].clear();
    }
    ans.clear();

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u > v)
            swap(u, v);
        key[i] = {u, v};

        G[u].push_back(v);
        G[v].push_back(u);
    }

    bcc(1);
    auto t = dfs(1);
    release(t);

    for (int i = 0; i < m; i++) {
        auto it = ans.find(key[i]);
        if (it != ans.end())
            printf("%d %d\n", it->second.u, it->second.v);
        else
            puts("0 0");
    }
}

void _main() {
    initialize();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
        // fprintf(stderr, "mempos = %zu\n", mempos);
    }
    return 0;
}