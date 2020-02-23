#include <cstdio>
#include <cctype>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE, _sz;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

#define NMAX 3000000
#define MOD 1000000007

#define EVAL 0
#define CALL 1
#define ENDP 2

typedef long long i64;

int m, n, q;
int type[NMAX + 10], in[NMAX + 10];
i64 c[NMAX + 10], ans[NMAX + 10];
vector<int> G[NMAX + 10];

void link(int u, int v) {
    G[u].push_back(v);
    in[v]++;
}

void initialize() {
    read(m); read(q);
    n = m;
    for (int i = 1; i <= m; i++) {
        type[i] = ENDP;
        int cnt;
        read(cnt);
        for (int j = 1; j <= cnt; j++) {
            link(i, n + j);
            int len;
            read(len);
            for (int k = 0; k < len; k++) {
                int v;
                read(v);
                link(n + j, n + v);
            }

            read(type[n + j]);
            if (type[n + j] == EVAL)
                read(c[n + j]);
            else {
                int v;
                read(v);
                link(n + j, v);
            }
        }
        n += cnt;
    }
}

int topo[NMAX + 10];

void tsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!in[i]) q.push(i);

    int p = n;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo[p--] = u;
        for (int v : G[u]) {
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
}

void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

void solve() {
    tsort();

    for (int i = 1; i <= n; i++) {
        int u = topo[i];

        if (type[u] == EVAL) {
            for (int v : G[u])
                ans[u] = max(ans[u], ans[v]);

            add(ans[u], c[u]);
        } else if (type[u] == CALL) {
            for (int v : G[u])
            if (type[v] == ENDP)
                c[u] = (ans[v] + 1) % MOD;

            for (int v : G[u])
            if (type[v] != ENDP)
                ans[u] = max(ans[u], ans[v]);

            add(ans[u], c[u]);
        } else {
            for (int v : G[u])
                ans[u] = max(ans[u], ans[v]);
        }
    }
}

int main() {
    initialize();
    solve();

    while (q--) {
        int u;
        read(u);
        printf("%lld\n", ans[u]);
    }

    return 0;
}