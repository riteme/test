#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 105;

int n, m, s;
int sum, node[MAXN];
int degree[MAXN];
bool vis[MAXN];
bool c[MAXN][MAXN];
vector<int> link[MAXN];
int _stack[MAXN], top;
int ans;

void dfs(int k, int j) {
    if (k == s) {
        ans++;
        return;
    }
    for (int i = j+1; i <= sum; i++) {
        bool check = true;
        for (int it = 1; it <= top; it++) {
            if (c[node[i]][node[_stack[it]]] == false) {
                check = false;
                break;
            }
        }

        if (sum - i + k >= s-1 && degree[node[i]] >= s-1 && check) {
            _stack[++top] = i;
            dfs(k+1, i);
            top--;
        }

        if (sum - i + k < s-1)
            return;
    }
}

int main() {
    int T;

    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &s);

        for (int i = 1; i <= n; i++)
            link[i].clear();
        memset(c, false, sizeof(c));
        memset(degree, 0, sizeof(degree));
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);

            degree[u]++; degree[v]++;
            c[u][v] = c[v][u] = true;
            link[u].push_back(v); link[v].push_back(u);
        }

        ans = 0;
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            if (degree[i] < s-1)
                continue;

            sum = 0;
            for (int j = 0; j < link[i].size(); j++) {
                if (degree[link[i][j]] < s-1 || vis[link[i][j]])
                    continue;

                node[++sum] = link[i][j];
            }

            top = 0;
            vis[i] = true;
            if (sum >= s-1)
                dfs(1, 0);
            else
                continue;

            for (int j = 1; j <= sum; j++)
                degree[node[j]]--;
        }

        printf("%d\n", ans);
    }
    return 0;
}
