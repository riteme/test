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

template <>
struct less<WeightedEdge> {
    constexpr bool operator()(const WeightedEdge &a,
                              const WeightedEdge &b) const {
        return a.dist < b.dist;
    }
};  // struct less

void Dijkstra(int v) {
    int cnt = 1;

    edgeTo.resize(G.VertexCount(), 0);
    distTo.resize(G.VertexCount(), INFINITY);
    pq.resize(G.VertexCount(), INFINITY);

    distTo[v] = 0.0;
    pq[v] = 0.0;

    while (cnt > 0) {
        auto m = std::min_element(pq.begin(), pq.end());
        int u = std::distance(pq.begin(), m);
        cnt--;

        for (auto &w : G.GetRelative(u)) {
            if (w.dist + distTo[w.from()] < distTo[w.to()]) {
                distTo[w.to()] = w.dist + distTo[w.from()];
                edgeTo[w.to()] = u;

                if (std::isinf(pq[w.to()])) { cnt++; }
                pq[w.to()] = distTo[w.to()];
            }
        }  // foreach in G.GetRelative(u)

        *m = INFINITY;
    }  // while
}

void PrintPath(int s, int e) {
    stack<int> st;

    for (int v = e; v != s; v = edgeTo[v]) { st.push(v); }  // for

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
    Dijkstra(s);

    for (int i = 1; i < G.VertexCount(); i++) { PrintPath(s, i); }  // for

    return 0;
}  // function main
