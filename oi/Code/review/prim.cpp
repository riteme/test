#include <cstdio>
#include <climits>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 50000

template <typename TCompare>
struct Heap {
    void push(int x) {
        _s.insert(x);
    }

    void pop(int x) {
        auto iter = _s.find(x);

        if (iter != _s.end())
            _s.erase(iter);
    }

    void pop() {
        _s.erase(_s.begin());
    }

    int top() const {
        return *_s.begin();
    }

    bool empty() const {
        return _s.empty();
    }

    multiset<int, TCompare> _s;
};

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};

static int n, m;
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static int weight[NMAX + 10];

struct Compare {
    bool operator()(const int a, const int b) const {
        return weight[a] < weight[b] || (weight[a] == weight[b] && a < b);
    }
};

static int prim() {
    int answer = 0;
    Heap<Compare> q;

    weight[1] = 0;
    q.push(1);
    for (int i = 2; i <= n; i++) {
        weight[i] = INT_MAX;
        q.push(i);
    }

    while (!q.empty()) {
        int u = q.top();
        marked[u] = true;
        answer += weight[u];
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (!marked[v] && e->w < weight[v]) {
                q.pop(v);
                weight[v] = e->w;
                q.push(v);
            }
        }
    }

    return answer;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }

    printf("%d\n", prim());

    return 0;
}
