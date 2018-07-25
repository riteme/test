#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define NMAX 1000

template <typename TCompare>
class Heap {
 public:
    void push(int x) {
        s.insert(x);
    }

    void pop(int x) {
        auto iter = s.find(x);

        assert(iter != s.end());
        s.erase(iter);
    }

    int top() {
        return *s.begin();
    }

    size_t size() const {
        return s.size();
    }

 private:
    multiset<int, TCompare> s;
};  // class Heap

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for
}

static bool marked[NMAX + 10];
static bool visited[NMAX + 10];
static int weight[NMAX + 10];

struct cmp {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] || (weight[a] == weight[b] && a < b);
    }
};  // struct cmp

int find_mincut(int &s, int &t) {
    Heap<cmp> q;
    memset(weight, 0, sizeof(weight));
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!marked[i])
            q.push(i);
    }  // for

    while (q.size() > 1) {
        int u = q.top();
        visited[u] = true;
        q.pop(u);

        s = u;
        for (auto &e : G[u]) {
            int v = e->either(u);

            if (visited[v])
                continue;

            q.pop(v);
            weight[v] += e->w;
            q.push(v);
        }  // foreach in G[u]
    }      // while

    t = q.top();
    return weight[t];
}

typedef pair<int, int> IntPair;

IntPair mincut(int cnt) {
    if (cnt < 2)
        return make_pair(INT_MAX, cnt);

    int s, t;
    int ans = find_mincut(s, t);

    marked[t] = true;
    for (auto &e : G[t]) {
        if (e->u == t)
            e->u = s;
        else
            e->v = s;

        G[s].push_back(e);
    }  // foreach e in G[t]

    IntPair ret = mincut(cnt - 1);
    if (ans <= ret.first)
        return make_pair(ans, cnt);
    return ret;
}

int main() {
    initialize();

    IntPair result = mincut(n);
    printf("%d %d\n", result.first, n - result.second + 1);

    return 0;
}  // function main
