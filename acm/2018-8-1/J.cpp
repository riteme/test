#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define INF 1000000000000000

static int n, m, K;

struct Node {
    Node(int _val)
        : val(_val), rank(1), lch(NULL), rch(NULL) {}

    int val, rank;
    Node *lch, *rch;
};

inline Node *cpy(Node *x) {
    return new Node(*x);
}

inline int rank_of(Node *x) {
    return x ? x->rank : 0;
}

inline Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    if (x->val > y->val) swap(x, y);
    x = cpy(x);
    x->rch = meld(x->rch, y);
    if (rank_of(x->rch) > rank_of(x->lch)) swap(x->lch, x->rch);
    x->rank = rank_of(x->lch) + 1;
    return x;
}

struct Heap {
    Heap() : size(0), sum(0), Q(NULL) {}

    int size;
    i64 sum;
    Node *Q;

    void push(int w) {
        size++;
        sum += w;
        Q = meld(Q, new Node(w));
        while (size > K) pop();
    }

    void pop() {
        size--;
        sum -= Q->val;
        Q = meld(Q->lch, Q->rch);
    }

    bool operator<(const Heap &z) const {
        return sum < z.sum;
    }
};

struct Edge {
    Edge(int _v, i64 _w) : v(_v), w(_w) {}

    int v;
    i64 w;
};

static vector<Edge *> G[NMAX + 10];
static Heap Q[NMAX + 10];
static bool exist[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(new Edge(v, w));
        G[v].push_back(new Edge(u, w));
    }
}

void dp() {
    for (int i = 2; i <= n; i++)
        Q[i].sum = INF;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (auto e : G[u]) {
            int v = e->v;
            Heap nQ = Q[u];
            nQ.push(e->w);
            if (nQ < Q[v]) {
                Q[v] = nQ;
                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    initialize();
    dp();
    printf("%lld\n", Q[n].sum);
    return 0;
}
