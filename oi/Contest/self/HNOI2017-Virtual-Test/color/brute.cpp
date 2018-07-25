#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static bool marked[NMAX + 10];
static int color[NMAX + 10];
static vector<int> G[NMAX + 10];

inline void connect(int u) {
    marked[u] = true;

    int tpow = 1;
    for (; u / tpow; tpow *= 10) {
        int pre = u / tpow;
        
        if (!pre)
            break;

        int suf = u % tpow;
        int d = pre % 10;
        pre /= 10;
        for (int i = d - 1; i >= d / 2; i--) {
            int v = pre * tpow * 10 + i * tpow + suf;
            G[u].push_back(v);
            
            if (!marked[v])
                connect(v);
        }
    }
}

void coloring(int x) {
    for (auto v : G[x]) {
        if (!color[v])
            coloring(v);
    }

    memset(marked, 0, sizeof(marked));
    for (auto v : G[x]) {
        marked[color[v]] = true;
    }

    int c = 1;
    while (marked[c]) {
        c++;
    }

    color[x] = c;
}

void initialize() {
    scanf("%d", &n);
    connect(n);
}

static int cnt[10];

int main() {
    initialize();
    coloring(n);

    for (int i = 0; i <= n; i++) {
        if (color[i])
            cnt[color[i]]++;
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int c;
        scanf("%d", &c);

        if (c <= 10)
            printf("%d\n", cnt[c]);
        else
            printf("0\n");
    }

    return 0;
}
