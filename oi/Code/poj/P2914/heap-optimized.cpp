/**
 * Heavy graph lead to TLE
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define NMAX 500

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int &select(int x) {
        return u == x ? u : v;
    }

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u + 1, v + 1, w);
        G[u + 1].push_back(e);
        G[v + 1].push_back(e);
    }  // for
}

static bool marked[NMAX + 10];
static bool visited[NMAX + 10];
static int weight[NMAX + 10];

struct Compare {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] || (weight[a] == weight[b] && a < b);
    }
};  // struct Compare

template <typename TCompare>
class Heap {
 public:
    void push(int x) {
        s.insert(x);
    }

    void pop() {
        s.erase(s.begin());
    }

    void pop(int x) {
        typename Implementor::iterator iter = s.find(x);

        assert(iter != s.end());
        s.erase(iter);
    }

    int top() const {
        return *s.begin();
    }

    size_t size() const {
        return s.size();
    }

    bool empty() const {
        return s.empty();
    }

 private:
    typedef multiset<int, TCompare> Implementor;

    Implementor s;
};  // class Heap

int find_mincut(int &s, int &t) {
    memset(visited, 0, sizeof(visited));
    memset(weight, 0, sizeof(weight));

    Heap<Compare> q;
    for (int i = 1; i <= n; i++) {
        if (!marked[i])
            q.push(i);
    }  // for

    while (q.size() > 1) {
        int u = q.top();
        q.pop();

        s = u;
        visited[u] = true;
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (!visited[v]) {
                q.pop(v);
                weight[v] += e->w;
                q.push(v);
            }
        }  // for
    }      // while

    t = q.top();
    return weight[t];
}

int mincut(int cnt) {
    if (cnt < 2)
        return INT_MAX;

    int s, t;
    int ans = find_mincut(s, t);

    marked[t] = true;
    for (size_t i = 0; i < G[t].size(); i++) {
        Edge *e = G[t][i];

        e->select(t) = s;
        G[s].push_back(e);
    }  // for

    return min(ans, mincut(cnt - 1));
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        memset(marked, 0, sizeof(marked));
        printf("%d\n", mincut(n));
    }  // while

    return 0;
}
