#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>

using namespace std;

inline int readint() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }

    return x;
}

#define OUTPUT_BUFFER 1000000
static size_t _pos = 0;
static char _buffer[OUTPUT_BUFFER];

inline void putint(int x) {
    _pos += sprintf(_buffer + _pos, "%d\n", x);
}

#define NMAX 40000
// #define NMAX 100

static int n, m;
static vector<int> G[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    for (int i = 1; i <= n; i++) {
        G[2 * i - 1].push_back(2 * i + n * 2);
        G[2 * i].push_back(2 * i - 1 + n * 2);
        G[2 * i + n * 2].push_back(2 * i - 1);
        G[2 * i - 1 + n * 2].push_back(2 * i);
    }  // for

    // For convinence, n is multiplied by two.
    n *= 2;

    for (int i = 0; i < m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v + n);
        G[v].push_back(u + n);
    }  // for
}

inline int rev(int x) {
    if (x > n)
        return x - n;
    return x + n;
}

static int cnt = 1;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static int id[NMAX + 10];
static bool marked[NMAX + 109];
static stack<int> stk;
static vector<int> block[NMAX + 10];

static void tarjan(int x) {
    dfn[x] = low[x] = cnt++;
    stk.push(x);

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!dfn[v])
            tarjan(v);
        if (!marked[v])
            low[x] = min(low[x], low[v]);
    }  // for

    if (dfn[x] == low[x]) {
        while (true) {
            int v = stk.top();
            stk.pop();

            marked[v] = true;
            id[v] = x;
            block[x].push_back(v);

            if (v == x)
                break;
        }  // while
    }
}

static vector<int> R[NMAX + 10];
static int degree[NMAX + 10];

static void construct_graph() {
    for (int u = 1; u <= n * 2; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (id[u] != id[v]) {
                R[id[v]].push_back(id[u]);
                degree[id[u]]++;
            }
        }  // for
    }      // for
}

static queue<int> vertex_queue;
static int topo_cnt = 0;
static int topo[NMAX + 10];

static void topological_sort() {
    for (int i = 1; i <= n * 2; i++)
        if (degree[i] == 0)
            vertex_queue.push(i);

    while (!vertex_queue.empty()) {
        int u = vertex_queue.front();
        vertex_queue.pop();

        topo[++topo_cnt] = u;

        for (size_t i = 0; i < R[u].size(); i++) {
            int v = R[u][i];

            if (degree[v] > 0) {
                degree[v]--;

                if (degree[v] == 0)
                    vertex_queue.push(v);
            }
        }  // for
    }      // while
}

#define NOT_DETERMINED 0
#define SELECTED 1
#define NOT_SELECTED 2

static char state[NMAX + 10];

static bool solve() {
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 1; i <= n; i++)
        if (id[i] == id[rev(i)])
            return false;

    construct_graph();
    topological_sort();

    for (int i = 1; i <= topo_cnt; i++) {
        int x = topo[i];
        if (state[x])
            continue;

        state[x] = SELECTED;

        queue<int> q;
        for (size_t pos = 0; pos < block[x].size(); pos++) {
            int v = block[x][pos];
            q.push(id[rev(v)]);
        }  // for

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (state[u])
                continue;

            state[u] = NOT_SELECTED;

            for (size_t pos = 0; pos < R[u].size(); pos++) {
                int v = R[u][pos];

                if (state[v] == NOT_DETERMINED)
                    q.push(v);
            }  // for
        }      // while
    }          // for

    return true;
}

int main() {
    freopen("spo.in", "r", stdin);
    freopen("spo.out", "w", stdout);
    initialize();

    if (!solve())
        puts("NIE");
    else {
        for (int i = 1; i <= n; i++)
            if (state[id[i]] == SELECTED)
                putint(i);
    }

    fwrite(_buffer, 1, _pos, stdout);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
