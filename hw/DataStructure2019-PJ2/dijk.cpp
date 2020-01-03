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

#define NMAX 3000000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    int v, w, id;
};

static int n, m;
static vector<Edge> G[NMAX + 10];
static bool en[NMAX + 10];

void initialize() {
    read(n); read(m);
    fill(en + 1, en + m + 1, true);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u); read(v); read(w);
        G[u].push_back({v, w, i});
        G[v].push_back({u, w, i});
    }
}

static i64 sum = 0, scnt = 0;

i64 query(int s, int t) {
    struct State {
        int u;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    static int tm[NMAX + 10], cur;
    static i64 d[NMAX + 10];
    cur += 2;

    i64 cnt = 0, ans = INF;
    i64 mx[2] = {0};
    tm[s] = cur, tm[t] = cur + 1;
    d[s] = d[t] = 0;
    priority_queue<State> q[2];
    q[0].push({s, 0});
    q[1].push({t, 0});
    while (!q[0].empty() || !q[1].empty()) {
        int i;
        if (!q[0].empty() && !q[1].empty())
            i = q[0].top().t < q[1].top().t ? 0 : 1;
        else i = q[0].empty() ? 1 : 0;

        auto _ = q[i].top();
        q[i].pop();

        int u = _.u;
        if (_.t > d[u]) continue;
        mx[i] = _.t;
        // printf("mx[%d] = %lld @%d\n", i, mx[i], u);

        for (auto &e : G[u]) if (en[e.id]) {
            cnt++;

            if (d[u] + e.w + mx[i ^ 1] >= ans)
                continue;

            int v = e.v;
            if (tm[v] >= cur && tm[v] != tm[u]) {
                ans = min(ans, d[u] + e.w + d[v]);
                // printf("ans = %lld\n", ans);
            } else {
                if (tm[v] < cur) {
                    tm[v] = tm[u];
                    d[v] = INF;
                }

                if (d[v] > d[u] + e.w) {
                    d[v] = d[u] + e.w;
                    q[i].push({v, d[v]});
                }
            }
        }
    }

    if (ans < INF) {
        fprintf(stderr, "cnt = %lld\n", cnt);
        sum += cnt;
        scnt++;
    }
    return ans == INF ? -1 : ans;
}

int main() {
    initialize();

    int q;
    read(q);
    while (q--) {
        int s, t, c;
        read(s); read(t); read(c);

        static int rm[NMAX + 10];
        for (int i = 0; i < c; i++) {
            read(rm[i]);
            en[rm[i]] = false;
        }

        printf("%lld\n", query(s, t));

        for (int i = 0; i < c; i++)
            en[rm[i]] = true;
    }

    fprintf(stderr, "%.3Lf\n", static_cast<long double>(sum) / scnt);
    return 0;
}