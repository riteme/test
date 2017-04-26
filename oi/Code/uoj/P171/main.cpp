#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 600

class UnionFind {
 public:
    int find(int x) {
        return _find(x);
    }

    void link(int u, int v) {
        u = _find(u);
        v = _find(v);

        if (u != v)
            set[u] = v;
    }
    
 private:
    int set[NMAX + 10];

    int _find(int x) {
        return set[x] ? set[x] = _find(set[x]) : x;
    }
};

class BlossomAlgorithm {
 public:
    void reset(int _n) {
        n = _n;
        memset(match, 0, sizeof(match));

        for (int i = 1; i <= n; i++) {
            G[i].clear();
        }
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int solve(int m) {
        int ret = 0;

        for (int i = m; i <= n; i++) {
            if (!match[i] && argument(i))
                ret++;
        }

        for (int i = 1; i < m; i++) {
            if (!match[i] && argument(i))
                ret++;
        }

        return ret;
    }

    int match[NMAX + 10];

 private:
    enum NodeType {
        UNKNOWN, ODD, EVEN
    };

    int n;
    vector<int> G[NMAX + 10];
    deque<int> q;
    int link[NMAX + 10];
    int mark[NMAX + 10];
    NodeType type[NMAX + 10];
    UnionFind uf;

    int lca(int u, int v) {
        static int t;
        t++;

        while (u) {
            u = uf.find(u);
            mark[u] = t;
            u = link[match[u]];
        }

        while (v) {
            v = uf.find(v);

            if (mark[v] == t)
                return v;

            v = link[match[v]];
        }

        return -1;
    }

    void process(int u, int p) {
        while (u != p) {
            int a = match[u];
            int b = link[a];

            if (type[a] == ODD) {
                type[a] = EVEN;
                q.push_back(a);
            }

            if (uf.find(b) != p)
                link[b] = a;

            uf.link(u, a);
            uf.link(a, b);
            u = b;
        }
    }
    
    bool argument(int s) {
        memset(&uf, 0, sizeof(uf));
        memset(link, 0, sizeof(link));
        memset(type, 0, sizeof(type));
        q.clear();
        q.push_back(s);
        type[s] = EVEN;

        while (!q.empty()) {
            int u = q.front();
            q.pop_front();

            for (int v : G[u]) {
                if (!type[v]) {
                    type[v] = ODD;
                    link[v] = u;

                    if (match[v]) {
                        type[match[v]] = EVEN;
                        q.push_back(match[v]);
                    } else {
                        while (link[v] != s) {
                            int a = link[v];
                            int b = match[a];
                            match[v] = a;
                            match[a] = v;
                            v = b;
                        }

                        match[v] = s;
                        match[s] = v;

                        return true;
                    }
                } else if (type[v] == EVEN &&
                           uf.find(u) != uf.find(v)) {
                    int p = lca(u, v);

                    if (uf.find(u) != p)
                        link[u] = v;
                    if (uf.find(v) != p)
                        link[v] = u;

                    process(u, p);
                    process(v, p);
                }
            }
        }

        return false;
    }
};

static int n, m, e, t;
static BlossomAlgorithm solver;

void initialize() {
    scanf("%d%d%d", &n, &m, &e);
    t = m * 3 + 2;
    solver.reset(n + t);

    for (int i = 1; i <= m; i++) {
        solver.add_edge(3 * i, 3 * i + 1);
        solver.add_edge(3 * i + 1, 3 * i + 2);
        solver.add_edge(3 * i + 2, 3 * i);
    }

    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        solver.add_edge(t + u, 3 * v);
        solver.add_edge(t + u, 3 * v + 1);
        solver.add_edge(t + u, 3 * v + 2);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        printf("%d\n", solver.solve(m * 3 + 3) - n);
        int *match = solver.match;
        for (int i = 1; i <= n; i++) {
            printf("%d ", match[m * 3 + 2 + i] / 3);
        }
        printf("\n");
    }

    return 0;
}
