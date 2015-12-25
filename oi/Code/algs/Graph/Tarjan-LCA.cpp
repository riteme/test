//
// Copyright 2015 riteme
//

#include <list>
#include <vector>
#include <iostream>

#include "../Interval/UnionFind/UnionFind.hpp"

using namespace std;

#define MARK_NONE 0
#define MARK_VISITED 1
#define MARK_PROCESSED 2

static int root;
static vector<list<int>> G;
static vector<int> ancestor;
static vector<char> marked;

void initialize();
void quit();

void LCA(UnionFind &uf, int u);

int main() {
    initialize();

    UnionFind uf(G.size() + 1);

    LCA(uf, root);

    quit();
    return 0;
}  // function main

void initialize() {
    int n;
    cin >> n >> root;

    G.resize(n + 1);
    ancestor.resize(n + 1);
    marked.resize(n + 1);

    int u, v;
    while (cin >> u >> v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }  // while
}

void quit() {}

// O(n^2)
void LCA(UnionFind &uf, int u) {
    marked[u] = MARK_VISITED;
    ancestor[uf.Find(u)] = u;

    for (auto v : G[u]) {
        if (marked[v] == MARK_NONE) {
            LCA(uf, v);
            uf.Union(u, v);
            ancestor[uf.Find(u)] = u;
        }
    }  // foreach in G[u]

    // O(n^2) ~ O(n)
    for (int v = 1; v < G.size(); v++) {
        if (v != u and marked[v] == MARK_PROCESSED) {
            cout << "LCA(" << u << ", " << v << ") is " << ancestor[uf.Find(v)]
                 << endl;
        }
    }  // for

    marked[u] = MARK_PROCESSED;
}
