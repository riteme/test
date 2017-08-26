#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define INF 0x3f3f3f3f

class Decoder {
 public:
    Decoder(FILE *file) : _pos(0) {
        fread(_buffer, 1, MAX_LENGTH, file);

        int v = 0;
        for (int i = 'a'; i <= 'z'; i++)
            _table[i] = v++;
        for (int i = 'A'; i <= 'Z'; i++)
            _table[i] = v++;
        for (int i = '0'; i <= '9'; i++)
            _table[i] = v++;
        _table['%'] = v++;
        _table['@'] = v++;
    }

    int next() {
        int r = _table[_buffer[_pos++]] << 18;
        r |= _table[_buffer[_pos++]] << 12;
        r |= _table[_buffer[_pos++]] << 6;
        r |= _table[_buffer[_pos++]];
        return r;
    }

 private:
    static const size_t MAX_LENGTH = 30000000;

    size_t _pos;
    char _buffer[MAX_LENGTH];
    int _table[256];
};

struct Edge {
    Edge(int _v, int _c) : pivot(false), v(_v), c(_c) {}
    bool pivot;
    int v, c;
    Edge *rev;
};

static int n, m, q, s, t;
static size_t pos[NMAX + 10];
static int dist[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

void link(int u, int v, int c) {
    Edge *e = new Edge(v, c);
    Edge *re = new Edge(u, 0);
    e->rev = re;
    re->rev = e;
    e->pivot = true;

    G[u].push_back(e);
    G[v].push_back(re);
}

void reset() {
    for (int i = 1; i < s; i++) {
        for (auto e : G[i]) {
            if (e->pivot) {
                e->c += e->rev->c;
                e->rev->c = 0;
            }
        }
    }
}

void bfs() {
    memset(dist, 0, sizeof(dist));
    dist[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e : G[u]) {
            int v = e->v;

            if (dist[v] || !e->c)
                continue;

            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

int dfs(int u, int maxflow) {
    if (u == t)
        return maxflow;

    int cur = 0;
    for (size_t &i = pos[u]; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->v;

        if (dist[u] + 1 != dist[v] || !e->c)
            continue;

        int flow = min(maxflow - cur, e->c);
        flow = dfs(v, flow);
        cur += flow;
        e->c -= flow;
        e->rev->c += flow;

        if (cur == maxflow)
            break;
    }

    return cur;
}

int dinic() {
    int ret = 0;
    while (true) {
        bfs();

        if (!dist[t])
            return ret;

        memset(pos + 1, 0, sizeof(size_t) * t);
        ret += dfs(s, INF);
    }
}

static Decoder *reader;

void initialize() {
    reader = new Decoder(stdin);
    // scanf("%d%d%d", &n, &m, &q);
    n = reader->next();
    m = reader->next();
    q = reader->next();

    s = 2 * n + 1;
    t = s + 1;
    for (int i = 1; i <= n; i++) {
        link(i, n + i, 1);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = reader->next();
        v = reader->next();
        link(n + u, v, 1);
        link(n + v, u, 1);
    }
}

int main() {
    initialize();

    while (q--) {
        int u, v, k;
        // scanf("%d%d%d", &u, &v, &k);
        u = reader->next();
        v = reader->next();
        k = reader->next();

        link(s, n + k, 2);
        link(n + u, t, 1);
        link(n + v, t, 1);

        putchar(dinic() == 2 ? '1' : '0');

        G[s].clear();
        G[t].clear();
        G[n + k].pop_back();
        G[n + u].pop_back();
        G[n + v].pop_back();
        reset();
    }

    return 0;
}
