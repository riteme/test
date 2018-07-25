#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 150000
#define QMAX 750000

struct Edge {
    Edge(int _u, int _v)
        : u(_u), v(_v), removed(false) {}

    int u, v;
    bool removed;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, q, s, xcnt, ycnt;
static vector<Edge *> G[NMAX + 10];
static Edge *e[QMAX + 10];
static int color[NMAX + 10];

bool test(int s) {
    queue<int> q;
    q.push(s);
    color[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            if (G[u][i]->removed)
                continue;

            int v = G[u][i]->either(u);

            if (color[v]) {
                if (color[v] == color[u])
                    return false;
            } else {
                color[v] = (color[u] == 1 ? 2 : 1);
                q.push(v);
            }
        }
    }

    return true;
}

void initialize() {
    scanf("%d%d%d", &n, &q, &s);
}

int main() {
    initialize();

    char command[4];
    for (int i = 1; i <= q; i++) {
        scanf("%s", command);

        if (command[0] == 'A') {
            int u, v;
            scanf("%d%d", &u, &v);

            if (s) {
                u ^= xcnt | ycnt;
                v ^= xcnt | ycnt;
            }

            e[i] = new Edge(u, v);
            G[u].push_back(e[i]);
            G[v].push_back(e[i]);
        } else {
            int pos;
            scanf("%d", &pos);
            e[pos]->removed = true;
        }

        bool answer = true;
        memset(color, 0, sizeof(color));
        for (int i = 1; i <= n; i++) {
            if (!color[i])
                answer &= test(i);
        }

        puts(answer ? "YES" : "NO");
        if (answer)
            xcnt++;
        else
            ycnt++;
    }

    return 0;
}
