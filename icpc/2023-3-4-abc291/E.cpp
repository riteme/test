#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

constexpr int NMAX = 200000;

int n, m;
int in[NMAX + 10];
vector<int> G[NMAX + 10];
int a[NMAX + 10], b[NMAX + 10];

bool solve() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0)
            q.push(i);
    }

    int i = 0;
    while (q.size()) {
        if (q.size() != 1)
            return false;

        int u = q.front();
        a[++i] = u;
        q.pop();
        for (int v : G[u]) {
            in[v]--;
            if (in[v] == 0)
                q.push(v);
        }
    }

    if (i != n)
        return false;

    for (int i = 1; i <= n; i++) {
        b[a[i]] = i;
    }

    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        in[v]++;
    }

    bool okay = solve();
    puts(okay ? "Yes" : "No");
    if (okay) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", b[i]);
        }
        puts("");
    }

    return 0;
}
