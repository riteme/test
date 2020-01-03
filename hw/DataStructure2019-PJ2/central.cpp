#include <cstdio>
#include <cctype>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 1000000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    int v, w, id;
};

static int n, m;
static vector<Edge> G[NMAX + 10];

void initialize() {
    read(n); read(m);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u); read(v); read(w);
        G[u].push_back({v, w, i});
        G[v].push_back({u, w, i});
    }
}

static i64 cnt[NMAX + 10];

void eval(int s) {
    struct State {
        int u;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    static i64 dist[NMAX + 10];
    static int len[NMAX + 10];
    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    priority_queue<State> q;
    dist[s] = len[s] = 0;
    q.push({s, 0});

    int mx = 0;
    while (!q.empty()) {
        auto s = q.top();
        q.pop();
        int u = s.u;
        if (s.t > dist[u])
            continue;
        for (auto &e : G[u]) {
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                len[v] = len[u] + 1;
                q.push({v, dist[v]});
            } else if (dist[v] == dist[u] + e.w)
                len[v] = min(len[v], len[u] + 1);
        }
    }

    for (int i = 1; i <= n; i++)
        mx = max(mx, len[i]);
    for (int i = 1; i <= n; i++)
        cnt[i] += len[i] * (mx - len[i]);
}

int main() {
    initialize();

    int q;
    read(q);
    while (q--) {
        int s, t, c;
        read(s); read(t); read(c);
        for (int i = 0; i < c; i++)
            read(t);
        eval(s);
    }

    sort(cnt + 1, cnt + n + 1, greater<i64>());
    for (int i = 1; i <= n; i++)
        printf("%lld,", cnt[i]);

    return 0;
}