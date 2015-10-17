#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

void BFS(const Graph &G, int s, vector<int> &edgeTo);
void BFS(const Graph &G, int v, vector<bool> &marked, vector<int> &edgeTo);
void PrintPath(int start, int end, vector<int> &edgeTo);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    Graph G;
    ReadIntoGraph(cin, G);
    cout << G.ToString();

    vector<int> edgeTo(G.VertexCount());

    BFS(G, 0, edgeTo);

    cout << endl;
    for (int v = 0; v < G.VertexCount(); v++) {
        PrintPath(0, v, edgeTo);
    }  // for

    return 0;
}  // function main

void BFS(const Graph &G, int s, vector<int> &edgeTo) {
    vector<bool> marked(G.VertexCount());

    BFS(G, s, marked, edgeTo);
}

void BFS(const Graph &G, int v, vector<bool> &marked, vector<int> &edgeTo) {
    queue<int> q;
    q.push(v);

    marked[v] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto w : G.GetRelative(current)) {
            if (!marked[w]) {
                q.push(w);
                marked[w] = true;
                edgeTo[w] = current;
            }
        }  // foreach in G.GetRelative(v)
    }      // while
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
