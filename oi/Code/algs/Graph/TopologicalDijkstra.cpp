#include <cmath>
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>

#include "WeightedGraph.hpp"

using namespace std;

static WeightedGraph G;
static vector<int> edgeTo;
static vector<double> distTo;
static vector<double> pq;
static list<int> topo;

template <>
struct less<WeightedEdge> {
    constexpr bool operator()(const WeightedEdge &a,
                              const WeightedEdge &b) const {
        return a.dist < b.dist;
    }
};  // struct less

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
            degree[e.to()]--;
        }  // foreach in G.GetRelative(v)

        cnt++;
    }  // while
}

WeightedEdge GetEdge(int v, int w) {
    for (auto u : G.GetRelative(v)) {
        if (w == u.to()) { return u; }
    }  // foreach in G.GetRelative(v)

    return { 0, 0, 0.0 };
}

void Dijkstra(int v) {
    edgeTo.resize(G.VertexCount(), -1);
    distTo.resize(G.VertexCount(), INFINITY);

    distTo[v] = 0.0;

    for (auto &u : topo) {
        for (auto &w : G.GetRelative(u)) {
            if (w.dist + distTo[w.from()] < distTo[w.to()]) {
                distTo[w.to()] = w.dist + distTo[w.from()];
                edgeTo[w.to()] = w.from();
            }
        }  // foreach in G.GetRelative(u)
    }      // foreach in G.GetRelative(u)
}

void PrintPath(int s, int e) {
    stack<int> st;

    for (int v = e; v != s; v = edgeTo[v]) {
        if (v == -1) { return; }

        st.push(v);
    }  // for

    cout << s;

    while (!st.empty()) {
        cout << " -> " << st.top();
        st.pop();
    }  // while

    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);

    ReadIntoDirectedWeightedGraph(cin, G);

    int s = 0;
    TopologicalSort();
    Dijkstra(s);

    for (int i = 1; i < G.VertexCount(); i++) { PrintPath(s, i); }  // for

    return 0;
}  // function main
