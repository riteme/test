#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 2000100;

int n, m, ecnt, s, t;
vector<int> G[NMAX + 10];
int match[NMAX + 10];

bool found;
bool marked[NMAX + 10];
bool greedy_matching(int x, int p) {
    marked[x] = true;

    for (int v : G[x]) if (v != p) {
        if (marked[v]) {
            if (!found) {
                found = true;
                match[x] = v;
                match[v] = x;
            }
        } else if (greedy_matching(v, x) && match[x] == 0) {
            match[x] = v;
            match[v] = x;
        }
    }

    return match[x] == 0;
}

void solve() {
    memset(marked + 1, 0, m + n + n + 2);
    for (int i = m + 1; i <= m + n + n; i++)
    if (!marked[i]) {
        found = false;
        greedy_matching(i, 0);
    };

    bool ok = all_of(match + m + 1, match + m + n + n + 1, [](int x) { return match[x] != 0; });
    if (ok) {
        puts("YES");

        vector<int> T1, T2;
        for (int i = 1; i <= m; i++) {
            if (match[i]) {
                int j = match[i] - m;
                if (j > n)
                    T1.push_back(i);
                else
                    T2.push_back(i);
            }
        }

        for (int i : T1) {
            printf("%d ", i);
        }
        puts("");
        for (int i : T2) {
            printf("%d ", i);
        }
        puts("");
    } else
        puts("NO");
}

void _link(int u, int v) {
    // printf("%d %d\n", u, v);

    G[u].push_back(v);
    G[v].push_back(u);
}

void link(int u, int v) {
    int i = ++ecnt;
    _link(m + u, i);
    _link(i, m + n + v);
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &s, &t) != EOF) {
        // printf("n=%d, m=%d, s=%d, t=%d\n", n, m, s, t);

        ecnt = 0;
        memset(match + 1, 0, sizeof(int) * (m + n + n + 2));
        for (int i = 1; i <= m + n + n + 2; i++) {
            G[i].clear();
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            link(u, v);
        }

        for (int i = 1; i <= 2; i++) {
            _link(m + t, m + n + n + i);
            _link(m + n + n + i, m + n + s);
        }

        solve();
    }

    return 0;
}