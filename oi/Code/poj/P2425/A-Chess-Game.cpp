/**
 * 考虑的方式比较不同
 * 首先应该考虑一个石子的情况，那么出度为0的点的SG函数为0
 * 因此，就变成了拓扑图上的游戏，可以DP计算每个点的SG值
 * 对于对个石子，应视为多个一个石子组合后的游戏
 * 根据SG定理就可以知道是m个点的SG函数异或和
 * 不为0时必胜
 */

#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n;
static int in[NMAX + 10];
static int out[NMAX + 10];
static int sg[NMAX + 10];
static vector<int> G[NMAX + 10];
static int topoorder[NMAX + 10];

static void topological_sort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0)
            q.push(i);
    }

    int pos = 1;
    while (!q.empty()) {
        int u = q.front();
        topoorder[pos++] = u;
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            in[v]--;
    
            if (in[v] == 0)
                q.push(v);
        }
    }
}

static bool mex[NMAX + 10];

static void dp() {
    for (int i = n; i >= 1; i--) {
        int u = topoorder[i];

        sg[u] = 0;
        if (out[u]) {
            for (size_t i = 0; i < G[u].size(); i++) {
                int v = G[u][i];

                mex[sg[v]] = true;
            }

            while (mex[sg[u]]) {
                sg[u]++;
            }

            for (size_t i = 0; i < G[u].size(); i++) {
                int v = G[u][i];

                mex[sg[v]] = false;
            }
        }
    }
}

static void initialize() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", out + i);

        G[i].clear();
        G[i].reserve(out[i]);
        for (int j = 0; j < out[i]; j++) {
            int x;
            scanf("%d", &x);
            x++;

            in[x]++;
            G[i].push_back(x);
        }
    }

    topological_sort();
    dp();
}

int main() {
    while (scanf("%d", &n) != EOF) {
        initialize();

        int cnt;
        while (scanf("%d", &cnt) != EOF) {
            if (!cnt)
                break;

            int g = 0;
            for (int i = 0; i < cnt; i++) {
                int x;
                scanf("%d", &x);
                x++;

                g ^= sg[x];
            }

            puts(g ? "WIN" : "LOSE");
        }
    }

    return 0;
}
