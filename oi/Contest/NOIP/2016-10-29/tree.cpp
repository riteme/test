#pragma GCC optimize(3)

#include <cstdio>
#include <cctype>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536

static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 1000000

typedef long long int64;

static int n;
static vector<int> G[NMAX + 10];
static vector<int> order;
static int64 dist[NMAX + 10];
static int64 size[NMAX + 10];
static bool marked[NMAX + 10];
static int64 answer[NMAX + 10];

static void bfs(int x) {
    queue<int> q;
    q.push(x);
    marked[x] = true;

    while (!q.empty()) {
        int u = q.front();
        order.push_back(u);
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if (marked[v])
                continue;

            marked[v] = true;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        answer[x] += dist[i];
        size[i] = 1;
    }

    for (int i = order.size() - 1; i >= 0; i--) {
        int u = order[i];
        marked[u] = false;

        for (size_t pos = 0; pos < G[u].size(); pos++) {
            int v = G[u][pos];

            if (marked[v])
                continue;

            size[u] += size[v];
        }
    }
}

static void dp() {
    for (size_t pos = 0; pos < order.size(); pos++) {
        int x = order[pos];
        marked[x] = true;

        for (size_t i = 0; i < G[x].size(); i++) {
            int v = G[x][i];

            if (marked[v])
                continue;
            
            answer[v] = answer[x] + n - 2 * size[v];
        }
    }
}

static void initialize() {
//    scanf("%d", &n);
    n = readint();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v);
        G[v].push_back(u);
    }

    bfs(1);
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    initialize();

    dp();

    int maxp = 0;
    for (int i = 1; i <= n; i++) {
        if (answer[i] > answer[maxp])
            maxp = i;
    }

    printf("%d\n", maxp);

    return 0;
}
