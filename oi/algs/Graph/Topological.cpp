#include <climits>
#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Graph.hpp"

using namespace std;

static Graph G;
static list<int> topo;

void TopologicalSort() {
    vector<int> degree(G.VertexCount());

    for (int i = 0; i < G.VertexCount(); i++) {
        degree[i] = G.GetIndegree(i);
    }  // for

    int cnt = 1;
    while (cnt <= G.VertexCount()) {
        auto m = std::min_element(degree.begin(), degree.end());
        auto v = std::distance(degree.begin(), m);
        *m = INT_MAX;

        topo.push_back(v);
        for (auto &e : G.GetRelative(v)) {
            degree[e]--;
        }  // foreach in G.GetRelative(v)

        cnt++;
    }  // while
}

void PrintTopological() {
    cout << topo.front();

    for (auto beg = ++topo.begin(); beg != topo.end(); beg++) {
        cout << " -> " << *beg;
    }  // foreach in topo

    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);

    ReadIntoDirectedGraph(cin, G);
    TopologicalSort();
    PrintTopological();

    return 0;
}  // function main
