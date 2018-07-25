/**
 * DFS序
 * 此题丧心病狂卡vector
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int s[NMAX + 10];
static int n;

inline int query(int r) {
    int answer = 0;

    for (int x = r; x; x -= x & (-x)) {
        answer += s[x];
    }  // for

    return answer;
}

inline void modify(int x, int v) {
    if (x == 0) {
        return;
    }

    for (; x <= n; x += x & (-x)) {
        s[x] += v;
    }  // for
}

inline int query(int left, int right) {
    return query(right) - query(left - 1);
}

// static vector<int> G[NMAX + 10];
static int G[NMAX + 10][100];
static bool marked[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static int current = 0;

static void dfs(int x) {
    in[x] = ++current;
    marked[x] = true;

    // for (unsigned i = 0; i < G[x].size(); i++) {
    for (int i = 1; i <= G[x][0]; i++) {
        int v = G[x][i];
        if (!marked[v]) {
            dfs(v);
        }
    }  // for

    out[x] = current;
}

static void read_graph() {
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u][++G[u][0]] = v;
        G[v][++G[v][0]] = u;
    }  // for
}

static void initialize() {
    scanf("%d", &n);

    read_graph();
    dfs(1);

    for (int i = 1; i <= n; i++) {
        modify(i, 1);
    }  // for
}

int main() {
    initialize();

    int m;
    scanf("%d", &m);

    char buffer[10];
    int x;
    while (m > 0) {
        scanf("%s%d", buffer, &x);

        switch (buffer[0]) {
            case 'C': {
                if (query(in[x], in[x]) >= 1) {
                    modify(in[x], -1);
                } else {
                    modify(in[x], 1);
                }
            } break;
            case 'Q': {
                printf("%d\n", query(in[x], out[x]));
            } break;
        }  // switch to buffer[0]

        m--;
    }  // while

    return 0;
}  // function main
