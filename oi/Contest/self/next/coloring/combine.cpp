#include <cstring>

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 10

struct Graph {
    int n, m;
    vector<int> adj[NMAX * NMAX + 1];

    friend istream &operator>>(istream &stream, Graph &g);
};

istream &operator>>(istream &stream, Graph &g) {
    stream >> g.n >> g.m;

    for (int i = 0; i < g.m; i++) {
        int u, v;
        stream >> u >> v;

        g.adj[u].push_back(v);
    }

    return stream;
}

static Graph G1, G2, G;

inline int hashing(int a, int b) {
    return a * 10 + b;
}

int main() {
    cin >> G1 >> G2;

    for (int a = 1; a <= G1.n; a++) {
        for (int b = 1; b <= G2.n; b++) {
            int u = hashing(a, b);

            for (size_t i = 0; i < G1.adj[a].size(); i++) {
                int p = G1.adj[a][i];
                int v = hashing(p, b);

                G.adj[u].push_back(v);
            }

            for (size_t i = 0; i < G2.adj[b].size(); i++) {
                int p = G2.adj[b][i];
                int v = hashing(a, p);

                G.adj[u].push_back(v);
            }
        }
    }

    vector<pair<int, int>> edges;
    for (int u = 1; u <= hashing(G1.n, G2.n); u++) {
        for (size_t i = 0; i < G.adj[u].size(); i++) {
            int v = G.adj[u][i];

            edges.push_back(make_pair(u, v));
        }
    }

    cout << hashing(G1.n, G2.n) << " " << edges.size() << endl;
    for (auto &e : edges) {
        cout << e.first << " " << e.second << endl;
    }

    return 0;
}
