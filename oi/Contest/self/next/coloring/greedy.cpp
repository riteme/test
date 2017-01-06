#include <cstring>
#include <cstdlib>

#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m, s;
static vector<int> G[NMAX + 1];
static bool marked[NMAX + 1];
static int color[NMAX + 1];

static void initialize() {
    cin >> n >> m >> s;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        G[u].push_back(v);
    }
}

static void coloring(int x) {
    bitset<NMAX + 1> mex;
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (v < x)
            continue;
        if (!marked[v])
            coloring(v);
        mex[color[v]] = true;
    }

    while (mex[color[x]]) {
        color[x]++;
    }
}

int main() {
    initialize();
    coloring(s);

    stringstream buffer;
    buffer << "digraph {" << endl;
    buffer << "    node [ shape = circle ];" << endl;

    for (int i = 1; i <= n; i++) {
        if (marked[i]) {
            buffer << "    " << i
                   << " [ label = \"" << i << "/" << color[i] << "\" ];"
                   << endl;
        }
    }

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            buffer << "    " << u << " -> " << v << ";" << endl;
        }
    }

    buffer << "}" << endl;
    ofstream writer("/tmp/graph.dot");
    writer << buffer.str();
    writer.close();
    
    system("showdot /tmp/graph.dot &");

    return 0;
}
