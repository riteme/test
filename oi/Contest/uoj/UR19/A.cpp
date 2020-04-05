#include <cstdio>
#include <cstring>

#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 310

typedef bitset<NMAX> vec;

int n, m;
vector<int> G[NMAX];
vec t, b[NMAX];
bool has[NMAX];

void solve() {
    scanf("%d%d", &n, &m);

    t.reset();
    memset(has + 1, 0, n);
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        b[i].reset();
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w) {
            t[u] = t[u] ^ 1;
            t[v] = t[v] ^ 1;
        }
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        vec z;
        if (G[i].size() & 1)
            z[i] = 1;
        for (int j : G[i])
            z[j] = 1;

        for (int j = 1; j <= n; j++) if (z[j]) {
            if (has[j])
                z ^= b[j];
            else {
                has[j] = true;
                b[j] = z;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    if (t[i] && has[i])
        t ^= b[i];

    puts(t.count() ? "no" : "yes");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}