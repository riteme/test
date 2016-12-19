#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 30000

static int n, m, q;
static int W[NMAX + 10];
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", W + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static int len;
static int value[NMAX + 10];
static int id[NMAX + 10];
static bool marked[NMAX + 10];

static bool find_path(int x, int t, int pos) {
    if (x == t) {
        value[pos] = W[t];
        id[pos] = t;
        len = pos;
        return true;
    }
    
    marked[x] = true;
    
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (marked[v])
            continue;

        if (find_path(v, t, pos + 1)) {
            value[pos] = W[x];
            id[pos] = x;

            return true;
        }
    }

    return false;
}

static bool cmp1(const int a, const int b) {
    return a < b;
}

static bool cmp2(const int a, const int b) {
    return a > b;
}   

int main() {
    initialize();

    while (m--) {
        int opt, u, v;
        scanf("%d%d%d", &opt, &u, &v);
        
        memset(marked, 0, sizeof(marked));
        find_path(u, v, 1);

        if (opt == 0)
            sort(value + 1, value + len + 1, cmp1);
        else
            sort(value + 1, value + len + 1, cmp2);

        for (int i = 1; i <= len; i++) {
            W[id[i]] = value[i];
        }
    }

    printf("%d\n", W[q]);

    return 0;
}
