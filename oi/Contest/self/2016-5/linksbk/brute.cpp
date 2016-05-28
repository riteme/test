#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define COLORMAX 1000000

static int color[NMAX + 10];

typedef bitset<COLORMAX + 10> ColorMap;

static int n, m;
static vector<int> G[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static int colordata[NMAX + 10];
static int timestamp;

static void dfs(int x) {
    in[x] = ++timestamp;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (in[v] == 0) {
            dfs(v);
        }
    }  // for

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);

        colordata[i] = c;
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    scanf("%d", &m);

    dfs(1);
    for (int i = 1; i <= n; i++) {
        color[in[i]] = colordata[i];
    }  // for
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    initialize();

    for (int i = 0; i < m; i++) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int u, c;
            scanf("%d%d", &u, &c);

            u = in[u];
            color[u] = c;
        } else {  // 1
            int u;
            scanf("%d", &u);

            int s = in[u], t = out[u];
            ColorMap map;
            int answer = 0;
            for (int j = s; j <= t; j++) {
                int c = color[j];
                if (!map.test(c)) {
                    map.set(c);
                    answer++;
                }
            }  // for

            printf("%d\n", answer);
        }
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
