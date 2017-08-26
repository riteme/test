#pragma GCC optimize(3)

#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }

    return _buf[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;

    do {
        c = _getchar();
    } while (!isdigit(c));

    do {
        x = x * 10 + (c - '0');
        c = _getchar();
    } while (isdigit(c));
}

#define NMAX 100000

static int n;
static int col[NMAX + 10];
static vector<int> G[NMAX + 10];
static int last[NMAX + 10];

void initialize() {
    read(n);

    for (int i = 1; i <= n; i++) {
        read(col[i]);
    }

    int u, v;
    for (int i = 0; i < n - 1; i++) {
        read(u);
        read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static int cnt;
static bitset<NMAX + 1> mark;

void dfs(int u, int f) {
    if (mark[col[u]])
        return;
    cnt++;
    mark[col[u]] = true;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (v == f)
            continue;

        dfs(v, u);
    }

    mark[col[u]] = false;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    initialize();

    long long ans = 0;
    if (n <= 5000) {
        for (int i = 1; i <= n; i++) {
            cnt = 0;
            dfs(i, 0);
            ans += cnt;
        }

        ans = (ans + n) / 2;
    } else {
        int maxr = 0;
        for (int i = 1; i <= n; i++) {
            maxr = max(maxr, last[col[i]]);
            last[col[i]] = i;
            ans += i - maxr;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
