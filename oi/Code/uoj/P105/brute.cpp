// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 200

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n;
static vector<Edge *> G[NMAX + 10];
static bool vistied[NMAX + 10][NMAX + 10];
static int f[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        Edge *e = new Edge(u, v, c);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for
}

int dp(int x, int k, int t) {
    if (vistied[x][k])
        return f[x][k];

    vistied[x][k] = true;
    int &answer = f[x][k] = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (v == t)
            continue;
        if (v == k)
            answer += dp(v, 0, x) + e->w;
        else {
            int maxp = 0;
            for (size_t j = 0; j < G[v].size(); j++) {
                Edge *e2 = G[v][j];
                int p = e2->either(v);

                if (p == x)
                    continue;
                if (maxp == 0 || dp(v, p, x) > dp(v, maxp, x))
                    maxp = p;
            }  // for

            if (maxp)
                answer += max(dp(v, 0, x), dp(v, maxp, x) + e->w);
            else
                answer += dp(v, 0, x);
        }
    }  // for

    return answer;
}

int main() {
    initialize();

    int answer = 0;
    for (int u = 1; u <= n; u++) {
        memset(vistied, 0, sizeof(vistied));
        memset(f, 0, sizeof(f));
        answer = max(answer, dp(u, 0, 0));
    }  // for

    printf("%d\n", answer);

    return 0;
}  // function main
