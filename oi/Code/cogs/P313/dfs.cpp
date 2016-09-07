#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>

using namespace std;

inline int readint() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }

    return x;
}

#define OUTPUT_BUFFER 1000000
static size_t _pos = 0;
static char _buffer[OUTPUT_BUFFER];

inline void putint(int x) {
    _pos += sprintf(_buffer + _pos, "%d\n", x);
}

#define NMAX 40000
// #define NMAX 100

#define NOT_DETERMINED 0
#define SELECTED 1
#define NOT_SELECTED 2

static int n, m;
static vector<int> G[NMAX + 10];
static vector<int> RG[NMAX + 10];
static char state[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    for (int i = 1; i <= n; i++) {
        G[2 * i - 1].push_back(2 * i + n * 2);
        G[2 * i].push_back(2 * i - 1 + n * 2);
        G[2 * i + n * 2].push_back(2 * i - 1);
        G[2 * i - 1 + n * 2].push_back(2 * i);
    }  // for

    // For convinence, n is multiplied by two.
    n *= 2;

    for (int i = 0; i < m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v + n);
        G[v].push_back(u + n);
    }  // for

    for (int i = 1; i <= n; i++) {
        for (size_t pos = 0; pos < G[i].size(); pos++) {
            RG[G[i][pos]].push_back(i);
        }  // for
    }      // for
}

inline int rev(int x) {
    if (x > n)
        return x - n;
    return x + n;
}

static bool marked[NMAX + 10];

static bool try_select(int x) {
    if (marked[x])
        return true;
    if (marked[rev(x)])
        return false;
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (state[v] == NOT_SELECTED)
            return false;

        if (state[v] == NOT_DETERMINED)
            if (!try_select(v))
                return false;
    }  // for

    return true;
}

static bool attempt(int x) {
    memset(marked, 0, sizeof(marked));

    if (state[x])
        return true;

    bool flag = try_select(x);

    if (flag) {
        for (int i = 1; i <= n; i++) {
            if (marked[i]) {
                state[i] = SELECTED;
                state[rev(i)] = NOT_SELECTED;
            }
        }  // for
    }

    return flag;
}

int main() {
    freopen("spo.in", "r", stdin);
    freopen("spo.out", "w", stdout);
    initialize();

    // Conculsion: weak data.
    // for (int i = 1; i <= n; i++) {  // TLE on COGS
    for (int i = n; i >= 1; i--) {  // AC on COGS
        // i must be true of false, instead of not determined.
        if (!attempt(i)) {
            if (!attempt(rev(i))) {
                puts("NIE");
                return 0;
            }
        }
    }  // for

    for (int i = 1; i <= n; i++) {
        if (state[i] == SELECTED) {
            // printf("%d\n", i);
            putint(i);
        }
    }  // for

    fwrite(_buffer, 1, _pos, stdout);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
