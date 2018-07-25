#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(const Graph &G, int s);
void BFS(const Graph &G, int v, vector<bool> &marked);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    Graph G;
    ReadIntoGraph(cin, G);
    cout << G.ToString();

    BFS(G, 0);

    return 0;
}  // function main

void BFS(const Graph &G, int s) {
    vector<bool> marked(G.VertexCount());

    BFS(G, s, marked);
}

void BFS(const Graph &G, int v, vector<bool> &marked) {
    queue<int> q;
    q.push(v);

    cout << v << " ";
    marked[v] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto w : G.GetRelative(current)) {
            if (!marked[w]) {
                q.push(w);
                marked[w] = true;
                cout << w << " ";
            }
        }  // foreach in G.GetRelative(v)
    }      // while

    cout << endl;
}
