#include "Graph.hpp"

#include <iostream>
#include <vector>

using namespace std;

void DFS(const Graph &G, int s);
void DFS(const Graph &G, int v, vector<bool> &marked);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    Graph G;
    ReadIntoGraph(cin, G);
    cout << G.ToString();

    DFS(G, 0);

    return 0;
}  // function main

void DFS(const Graph &G, int s) {
    vector<bool> marked(G.VertexCount());
    cout << s << " ";

    DFS(G, s, marked);

    cout << endl;
}

void DFS(const Graph &G, int v, vector<bool> &marked) {
    for (auto w : G.GetRelative(v)) {
        marked[v] = true;

        if (!marked[w]) {
            cout << w << " ";
            DFS(G, w, marked);
        }
    }  // foreach in G.GetRelative(v)
}
