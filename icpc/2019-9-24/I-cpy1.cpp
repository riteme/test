#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <unordered_set>
#include <algorithm>

using namespace std;

#define NMAX 52
#define BUCSIZE 1499977
#define CMAX 4000000
#define BASE 19260817

typedef unsigned int u32;
typedef unsigned long long u64;

inline u64 H(char *s, int n) {
    u64 r = 0;
    u32 *p = reinterpret_cast<u32*>(s);
    for (int i = 0; i < n; i += 4, p++) r = r * BASE + *p;
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

void dfs(int i) {
    if (i == m) tb.push(H(s, n));
    else if (s[u[i]] < s[v[i]]) {
        dfs(i + 1);
        swap(s[u[i]], s[v[i]]);
        dfs(i + 1);
        swap(s[u[i]], s[v[i]]);
    }
}

int main() {
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
            for (int j = i - 1; j >= 0; j--) {
                swap(s[j], s[j + 1]);
                u64 x = H(s, n);
                if (used.count(x)) continue;
                used.insert(x);
                dfs(0);
            }
            for (int j = 0; j < n; j++) s[j] = j + 1;
            for (int j = i + 1; j < n; j++) {
                swap(s[j], s[j - 1]);
                u64 x = H(s, n);
                if (used.count(x)) continue;
                used.insert(x);
                dfs(0);
            }
        }
        printf("%d\n", tb.cnt);
    }
    return 0;
}
