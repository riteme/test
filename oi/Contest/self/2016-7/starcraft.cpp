#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

#define NMAX 1000
#define MMAX 500
#define TMAX 4000

static int n, m, x;
static vector<int> G[NMAX + 10];
static int length[NMAX + 10];
static vector<int> leaves;
static int w[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static int dist[NMAX + 10];

static void generate_dfs_seq(int x) {
    in[x] = ++timestamp;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        dist[v] = dist[x] + length[v];
        generate_dfs_seq(G[x][i]);
    }  // for

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; i++) {
        int p, f, l;
        scanf("%d%d%d", &p, &f, &l);
        G[f].push_back(p);
        length[p] = l;
    }  // for

    for (int i = 1; i <= n; i++) {
        if (G[i].empty())
            leaves.push_back(i);
    }  // for
    x = leaves.size();

    for (int i = 0; i < x; i++) {
        int p, weight;
        scanf("%d%d", &p, &weight);
        w[p] = weight;
    }  // for

    generate_dfs_seq(1);

    for (int i = 1; i <= n; i++) {
        dist[i] *= 2;
    }  // for
}

static int f[TMAX + 10];

static int solve(int selected, int t) {
    printf("in[selected] = %d, out[selected] = %d\n", in[selected],
           out[selected]);
    for (unsigned i = 0; i < leaves.size(); i++) {
        int v = leaves[i];
        printf("Dp: %d, in[v] = %d\n", v, in[v]);
        if (in[selected] <= in[v] && in[v] <= out[selected]) {
            printf("Skipped %d\n", v);
            continue;
        }

        for (int j = t; j >= dist[v]; j--) {
            f[j] = max(f[j], f[j - dist[v]] + w[v]);
        }  // for
    }      // for

    return f[t];
}

static void print(stringstream &buffer, int x) {
    buffer << x << "[label=\"" << x << ": " << w[x] << ", " << dist[x]
           << "\"];";
    for (unsigned i = 0; i < G[x].size(); i++) {
        buffer << x << "->" << G[x][i] << "[label=\"" << length[G[x][i]]
               << "\"];";
        print(buffer, G[x][i]);
    }  // for
}

static void show() {
    stringstream buffer;
    buffer << "digraph {";

    print(buffer, 1);

    buffer << "}";

    ofstream file("/tmp/starcraft.tmp.dot");
    file << buffer.str();
    file.close();
    system("showdot /tmp/starcraft.tmp.dot &");
}

int main() {
    initialize();
    show();

    for (int i = 0; i < m; i++) {
        int p, t;
        scanf("%d%d", &p, &t);
        memset(f, 0, sizeof(f));
        printf("%d\n", solve(p, t));
    }  // for

    return 0;
}  // function main
