#pragma GCC optimize(3)
#pragma GCC optimize("-Ofast")

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000000

inline int digit(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return 26 + c - 'A';
    if ('0' <= c && c <= '9') return 52 + c - '0';
    return c == '!' ? 62 : 63;
}

inline int parse(const char *s, int m) {
    int r = 0;
    for (int i = 0; i < m; i++) r = r * 64 + digit(s[i]);
    return r;
}

static int n, w[NMAX + 10], ans[NMAX + 10];
static vector<int> ch[NMAX + 10];
static char buf[NMAX * 5 + 10];
static int tail, st[NMAX + 10];

void bfs(int p, int t) {
    queue<int> q;
    q.push(p);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[u] = t;
        for (int v : ch[u]) {
            if (w[v] == t) st[tail++] = v;
            else q.push(v);
        }
    }
}

void expand(int t) {
    int m = tail;
    for (int i = 0; i < m; i++) bfs(st[i], t);
    tail -= m;
    memmove(st, st + m, sizeof(int) * tail);
}

int main() {
    scanf("%d", &n);
    scanf("%s", buf);
    for (int i = 1; i <= n; i++)
        ch[parse(buf + 4 * i - 4, 4)].push_back(i);
    scanf("%s", buf);
    for (int i = 1; i <= n; i++)
        w[i] = parse(buf + 5 * i - 5);
    st[tail++] = 0;
    return 0;
}
