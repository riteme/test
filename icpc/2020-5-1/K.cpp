#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000

int n;
bool col[NMAX + 10], mark[NMAX + 10];
vector<int> G[NMAX + 10];

void link(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

void bfs(int s) {
    queue<int> q;
    q.push(s);
    mark[s] = true;
    do {
        int u = q.front();
        q.pop();
        for (int v : G[u]) if (!mark[v]) {
            mark[v] = true;
            col[v] = col[u] ^ 1;
            q.push(v);
        }
    } while (!q.empty());
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v);
    }

    for (int i = 1; i <= n; i++)
        link(2 * i - 1, 2 * i);

    for (int i = 1; i <= 2 * n; i++)
        if (!mark[i]) bfs(i);

    for (int i = 1; i <= 2 * n; i++)
        putchar(col[i] ? 'X' : 'Y');
    puts("");

    return 0;
}