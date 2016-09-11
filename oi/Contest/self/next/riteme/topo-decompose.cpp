#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define NMAX 100

static int n, m;
static vector<int> G[NMAX + 10];
static vector<int> GR[NMAX + 10];
static int indegree[NMAX + 10];
static int outdegree[NMAX + 10];  // #

static int tmp[NMAX + 10];
static int topo[NMAX + 10];
static int rtopo[NMAX + 10];

static void topological_sort() {
    memcpy(tmp, indegree, sizeof(tmp));

    queue<int> q;

    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);

    int pos = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo[pos++] = u;
        for (int v : G[u]) {
            tmp[v]--;

            if (tmp[v] == 0)
                q.push(v);
        }  // foreach in G[u]
    }      // while

    memcpy(rtopo, topo, sizeof(topo));
    reverse(rtopo + 1, rtopo + n + 1);
}

static int height[NMAX + 10];

static void evaluate_height() {
    for (int i = 1; i <= n; i++)
        if (outdegree[i] == 0)
            height[i] = 1;

    for (int i = 1; i <= n; i++) {
        int u = rtopo[i];

        for (int v : G[u]) {
            height[v] = max(height[v], height[u] + 1);
        }  // foreach in G[u]
    }      // for
}

static bool mergable[NMAX + 10];
static int head[NMAX + 10];
static bool marked[NMAX + 10];

static void real_decompose(int x) {
    marked[x] = true;

    int next = 0;
    for (int v : G[x]) {
        if (!marked[v] && height[v] > height[next])
            next = v;
    }  // foreach in G[x]

    if (next != 0) {
        head[next] = head[x];
        real_decompose(next);
    }
}

static void decompose() {
    for (int i = 1; i <= n; i++) {
        int u = topo[i];

        if (indegree[u] > 1)
            mergable[u] = true;

        if (!marked[u]) {
            head[u] = u;
            real_decompose(u);
        }
    }  // for
}

static void generate_dot(int x, stringstream &buffer) {
    marked[x] = true;

    buffer << x;
    if (mergable[x])
        buffer << " [ color = blue ];" << endl;
    else
        buffer << ";" << endl;

    for (int v : G[x]) {
        buffer << x << " -> " << v;

        if (head[x] == head[v])
            buffer << " [ color = red];" << endl;
        else
            buffer << ";" << endl;

        if (!marked[v])
            generate_dot(v, buffer);
    }  // foreach in G[x]
}

static void print() {
    memset(marked, 0, sizeof(marked));

    stringstream buffer;
    buffer << "digraph {" << endl;
    buffer << "node [ shape = circle ];" << endl;

    for (int i = 1; i <= n; i++) {
        if (!marked[i])
            generate_dot(i, buffer);
    }  // for

    buffer << "}" << endl;
    ofstream file("/tmp/topo-decompose.dot");
    file << buffer.str();
    file.close();

    system("showdot /tmp/topo-decompose.dot &");
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        GR[v].push_back(u);
        indegree[v]++;
        outdegree[u]++;
    }  // for

    topological_sort();
    evaluate_height();
    decompose();
}

int main() {
    initialize();
    print();

    return 0;
}  // function main
