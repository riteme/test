#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <unordered_set>
#include <algorithm>

using namespace std;

#define NMAX 50
#define BUCSIZE 1499977
#define CMAX 4000000
#define BASE 19260817

typedef unsigned int u32;
typedef unsigned long long u64;

static u64 pw[NMAX + 10];

inline u64 H(char *s, int n) {
    u64 r = 0;
    for (int i = 0; i < n; i++) r += s[i] * pw[i];
    return r;
}

static struct HashTable {
    int head[BUCSIZE], nxt[CMAX + 10], cnt;
    u64 key[CMAX + 10];

    void clear() {
        cnt = 0;
        memset(head, 0, sizeof(head));
    }

    void push(u64 x) {
        int p = x % BUCSIZE;
        for (int i = head[p]; i; i = nxt[i])
            if (key[i] == x) return;
        key[++cnt] = x;
        nxt[cnt] = head[p];
        head[p] = cnt;
    }
} tb;

static int n, m, _;
static int u[NMAX + 10], v[NMAX + 10];
static char s[NMAX + 10];
static u64 X;

void dfs(int i) {
    if (i == m) tb.push(X);
    else if (s[u[i]] < s[v[i]]) {
        dfs(i + 1);
        u64 X_ = X;
        X += s[u[i]] * (pw[v[i]] - pw[u[i]]) + s[v[i]] * (pw[u[i]] - pw[v[i]]);
        swap(s[u[i]], s[v[i]]);
        dfs(i + 1);
        swap(s[u[i]], s[v[i]]);
        X = X_;
    }
}

int main() {
    pw[0] = BASE;
    for (int i = 1; i <= NMAX; i++) pw[i] = pw[i - 1] * BASE;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &_);
        for (int i = 0; i < m; i++) scanf("%d%d", u + i, v + i);
        for (int i = 0; i < m; i++) {
            u[i]--;
            v[i]--;
        }
        reverse(u, u + m);
        reverse(v, v + m);

        tb.clear();
        for (int i = 0; i < n; i++) s[i] = i + 1;
        dfs(0);
        unordered_set<u64> used;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) s[j] = j + 1;
            X = H(s, n);
            for (int j = i - 1; j >= 0; j--) {
                X -= s[j] * pw[j] + s[j + 1] * pw[j + 1];
                swap(s[j], s[j + 1]);
                X += s[j] * pw[j] + s[j + 1] * pw[j + 1];
                if (used.count(X)) continue;
                used.insert(X);
                dfs(0);
            }
            for (int j = 0; j < n; j++) s[j] = j + 1;
            X = H(s, n);
            for (int j = i + 1; j < n; j++) {
                X -= s[j] * pw[j] + s[j - 1] * pw[j - 1];
                swap(s[j], s[j - 1]);
                X += s[j] * pw[j] + s[j - 1] * pw[j - 1];
                if (used.count(X)) continue;
                used.insert(X);
                dfs(0);
            }
        }
        printf("%d\n", tb.cnt);
    }
    return 0;
}
