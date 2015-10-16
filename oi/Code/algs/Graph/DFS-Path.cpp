#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(const Graph &G, int s, vector<int> &edgeTo);
void DFS(const Graph &G, int v, vector<bool> &marked, vector<int> &edgeTo);
void PrintPath(int start, int end, vector<int> &edgeTo);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    Graph G;
    ReadIntoGraph(cin, G);
    cout << G.ToString();

    vector<int> edgeTo(G.VertexCount());

    DFS(G, 0, edgeTo);

    cout << endl;
    for (int v = 0; v < G.VertexCount(); v++) {
        PrintPath(0, v, edgeTo);
    }  // for

    return 0;
}  // function main

void DFS(const Graph &G, int s, vector<int> &edgeTo) {
    vector<bool> marked(G.VertexCount());

    DFS(G, s, marked, edgeTo);
}

void DFS(const Graph &G, int v, vector<bool> &marked, vector<int> &edgeTo) {
    for (auto w : G.GetRelative(v)) {
        marked[v] = true;

        if (!marked[w]) {
            edgeTo[w] = v;
            DFS(G, w, marked, edgeTo);
        }
    }  // foreach in G.GetRelative(v)
}

void PrintPath(int start, int end, vector<int> &edgeTo) {
    cout << start << " to " << end << ": ";

    if (start == end) {
        cout << "Self loop" << endl;
        return;
    }

    stack<int> s;

    for (int v = end; v != start; v = edgeTo[v]) { s.push(v); }  // for

    cout << start << "-";

    while (s.size() > 1) {
        cout << s.top() << "-";
        s.pop();
    }  // while

    cout << s.top() << endl;
}
