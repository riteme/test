#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500000

struct Query {
    int x, y;
    bool answer;
};

enum NodeType {
    Normal,
    Cup,
    Cap,
    CupAndCap
};

static int n, m;
static int qcnt;
static Query querys[NMAX + 10];
static int pcnt;
static NodeType kind[NMAX + 10];
static bool used[NMAX + 10];
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);
    pcnt = n;

    for (int i = 1; i <= n; i++)
        kind[i] = Normal;

    while (m--) {
        int type;
        scanf("%d", &type);

        switch (type) {
            case 0: {
                int op, k;
                scanf("%d%d", &op, &k);

                pcnt++;
                if (k == 1)
                    kind[pcnt] = CupAndCap;
                else if (op == 0)
                    kind[pcnt] = Cap;
                else
                    kind[pcnt] = Cup;

                for (int i = 0; i < k; i++) {
                    int v;
                    scanf("%d", &v);

                    used[v] = true;
                    G[pcnt].push_back(v);
                }
            } break;

            case 1: {
                int x, y;
                scanf("%d%d", &x, &y);

                qcnt++;
                querys[qcnt].x = x;
                querys[qcnt].y = y;
            }
        }
    }
}

static int dist[NMAX + 10];
static int capcnt[NMAX + 10];
static int cupcnt[NMAX + 10];
static int father[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];

static void dfs(int x) {
    in[x] = ++timestamp;

    if (kind[x] == Cap || kind[x] == CupAndCap)
        capcnt[x]++;
    if (kind[x] == Cup || kind[x] == CupAndCap)
        cupcnt[x]++;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dist[v] = dist[x] + 1;
        father[v] = x;
        capcnt[v] = capcnt[x];
        cupcnt[v] = cupcnt[x];
        dfs(v);
    }

    out[x] = timestamp;
}

inline bool is_father(int x, int p) {
    return in[p] <= in[x] && in[x] <= out[p];
}

int main() {
    freopen("friendship.in", "r", stdin);
    freopen("friendship.out", "w", stdout);
    initialize();

    for (int i = 1; i <= pcnt; i++) {
        if (!used[i])
            dfs(i);
    }

    for (int i = 1; i <= qcnt; i++) {
        int x, y;
        x = querys[i].x;
        y = querys[i].y;

        if (is_father(x, y)) {
            if (cupcnt[father[x]] - cupcnt[father[y]] == dist[x] - dist[y])
                puts("1");
            else
                puts("0");
        } else if (is_father(y, x)) {
            if (capcnt[father[y]] - capcnt[father[x]] == dist[y] - dist[x])
                puts("1");
            else
                puts("0");
        } else {
            puts("0");
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
