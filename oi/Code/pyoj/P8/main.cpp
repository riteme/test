/**
 * Ancestor finding is O(n log n) - O(1) with help of long-chain decompose.
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

#define NMAX 200000
#define LOGN 18

static int n;
static int x[NMAX + 10];
static int k[NMAX + 10];
static int timestamp[NMAX + 10];
static set<int> sorted;
static vector<int> G[NMAX + 10];
static int depth[NMAX + 10];
static int rnk[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static int top[NMAX + 10];
static int len[NMAX + 10];
static vector<int> chain[NMAX + 10];
static int highbit[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", x + i, k + i);
    }  // for
}

void construct_tree() {
    sorted.insert(x[1]);

    for (int i = 2; i <= n; i++) {
        int u = x[i];
        auto iter = sorted.upper_bound(u);

        if (iter == sorted.end())
            iter = prev(iter);
        else if (prev(iter) != sorted.end() &&
                 timestamp[*iter] < timestamp[*prev(iter)])
            iter--;

        G[*iter].push_back(u);
        timestamp[u] = i;
        sorted.insert(u);
    }  // for
}

void build_tree(int x) {
    rnk[x] = 1;

    for (int v : G[x]) {
        f[0][v] = x;
        depth[v] = depth[x] + 1;

        build_tree(v);

        rnk[x] = max(rnk[x], rnk[v] + 1);
    }  // foreach in G[x]
}

void decompose(int x) {
    int next = 0;
    for (int v : G[x]) {
        if (rnk[v] > rnk[next])
            next = v;
    }  // foreach in G[x]

    if (next) {
        top[next] = top[x];
        decompose(next);
    }

    chain[top[x]].push_back(x);

    if (x == top[x]) {
        len[x] = chain[x].size();

        int u = f[0][x];
        for (int i = len[x]; i && u; i--, u = f[0][u]) {
            chain[x].push_back(u);
        }  // for
    }

    for (int v : G[x]) {
        if (v != next) {
            top[v] = v;
            decompose(v);
        }
    }  // foreach in G[x]
}

void build_highbits() {
    int ptr = 0;
    for (int i = 1; i <= n; i++) {
        while ((i >> (ptr + 1)) & 1) {
            ptr++;
        }  // while

        highbit[i] = ptr;
    }  // for
}

// O(1)
int query(int u, int d) {
    if (d == 0)
        return u;

    int h = highbit[d];
    u = f[h][u];
    d -= 1 << h;

    assert(d < (1 << h));

    int t = top[u];
    int pos = len[t] - 1 - (depth[u] - depth[t]) + d;

    assert(0 <= pos && pos < chain[t].size());

    return chain[t][pos];
}

int main() {
    initialize();

    construct_tree();
    build_tree(x[1]);

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }  // for
    }      // for

    top[x[1]] = x[1];
    decompose(x[1]);
    build_highbits();

    for (int i = 1; i <= n; i++) {
        printf("%d\n", query(x[i], depth[x[i]] - k[i] + 1));
    }  // for

    return 0;
}  // function main
