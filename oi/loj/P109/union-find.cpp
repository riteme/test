#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

#define NMAX 4000000
#define MOD 998244353
#define BUFFERSIZE 65536

static size_t pos = BUFFERSIZE;
static char buf[BUFFERSIZE];

inline void _getchar(char &c) {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buf, 1, BUFFERSIZE, stdin);
    }
    c = buf[pos++];
}

inline void read(int &x) {
    x = 0;
    register char c;
    do {
        _getchar(c);
    } while (!isdigit(c));
    
    do {
        x = x * 10 + (c - '0');
        _getchar(c);
    } while (isdigit(c));
}

static int ans, fa[NMAX + 1];

inline int find(int x) {
    return fa[x] > 0 ? fa[x] = find(fa[x]) : x;
}

inline void link(int x, int y) {
    if (x == y) return;
    if (fa[x] > fa[y]) fa[x] = y;
    else {
        fa[y] = x;
        if (fa[x] == fa[y]) fa[x]--;
    }
}

int main() {
    register int n, m, op, u, v;
    read(n); read(m);

    while (m--) {
        read(op); read(u); read(v);
        if (op) {
            ans = (ans << 1) | (find(u + 1) == find(v + 1));
            if (ans >= MOD) ans -= MOD;
        } else link(find(u + 1), find(v + 1));
    }

    printf("%d\n", ans);
}
