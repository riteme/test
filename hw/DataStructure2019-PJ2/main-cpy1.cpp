// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <queue>
#include <random>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define DEBUG(message, ...) fprintf(stderr, "⇒ " message "\n", __VA_ARGS__);
#define DPUTS(message) fputs(message "\n", stderr);
#else
#define DEBUG(...)
#define DPUTS(...)
#endif

typedef long long i64;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct Reader {
    static constexpr int BUFFERSIZE = 65536;

    size_t pos;
    char *buffer;

    Reader() : pos(0), buffer(new char[BUFFERSIZE]) {}
    ~Reader() { delete[] buffer; }

    char getc() {
        if (pos == BUFFERSIZE) {
            pos = 0;
            auto cnt = fread(buffer, 1, BUFFERSIZE, stdin);
            if (cnt < BUFFERSIZE)
                buffer[cnt] = 0;
        }
        return buffer[pos++];
    }

    template <typename T>
    void read(T &x) {
        char c;
        x = 0;
        do c = getc(); while (!isdigit(c));
        do {
            x = x * 10 + c - '0';
            c = getc();
        } while (isdigit(c));
    }

    template <typename T>
    void operator()(T &x) {
        read(x);
    }

    template <typename T, typename ... TArgs>
    void operator()(T &x, TArgs& ...args) {
        read(x);
        (*this)(args...);
    }
};

struct Edge {
    int v, w, id;
};

struct Graph {
    typedef vector<Edge> AdjacencyList;

    int n;
    AdjacencyList *adj;

    Graph() : n(0), adj(nullptr) {}
    Graph(int _n) : n(_n), adj(new AdjacencyList[n]) {}
    Graph(const Graph &G) : n(G.n), adj(new AdjacencyList[n]) {
        for (int i = 0; i < n; i++)
            adj[i] = G.adj[i];
    }
    Graph(Graph &&G) : n(G.n), adj(G.adj) {
        G.n = 0;
        G.adj = nullptr;
    }
    ~Graph() { if (adj) delete[] adj; }

    auto operator=(const Graph &G) -> Graph& {
        if (adj) delete[] adj;
        n = G.n;
        adj = new AdjacencyList[n];
        for (int i = 0; i < n; i++)
            adj[i] = G.adj[i];
        return *this;
    }

    auto operator=(Graph &&G) -> Graph& {
        if (adj) delete[] adj;
        n = G.n;
        adj = G.adj;
        G.n = 0;
        G.adj = nullptr;
        return *this;
    }

    void link(int u, int v, int w, int id = 0) {
        adj[u - 1].push_back({v, w, id});
        adj[v - 1].push_back({u, w, id});
    }

    void clear() {
        for (int i = 0; i < n; i++)
            adj[i].clear();
    }

    auto operator[](int u) -> AdjacencyList& {
        return adj[u - 1];
    }

    auto operator[](int u) const -> const AdjacencyList& {
        return adj[u - 1];
    }
};

struct SPTree {
    int /* *fa,  */*eid;

    SPTree() : /* fa(nullptr),  */eid(nullptr) {}
    SPTree(int n) : /* fa(new int[n + 1]),  */eid(new int[n + 1]) {}
    SPTree(const SPTree &) = delete;
    SPTree(SPTree &&rhs) : /* fa(rhs.fa),  */eid(rhs.eid) {
        /* rhs.fa = */ rhs.eid = nullptr;
    }

    auto operator=(const SPTree &) = delete;
    auto operator=(SPTree &&rhs) -> SPTree& {
        /* fa = rhs.fa; */
        eid = rhs.eid;
        /* rhs.fa = */ rhs.eid = nullptr;
        return *this;
    }

    ~SPTree() {
        /* if (fa)
            delete[] fa; */
        if (eid)
            delete[] eid;
    }
};

struct SPFAAlgorithm {
    int n;
    bool *mark;
    i64 *dist;

    SPFAAlgorithm(int _n) : n(_n),
        mark(new bool[n + 1]),
        dist(new i64[n + 1]) {
        memset(mark + 1, 0, n);
    }
    ~SPFAAlgorithm() {
        delete[] mark;
        delete[] dist;
    }

    auto operator()(const Graph &G, int s) -> SPTree {
        memset(dist + 1, 0x3f, sizeof(i64) * n);
        dist[s] = 0;

        deque<int> q;
        SPTree tr(n);
        q.push_back(s);
        /* tr.fa[s] = */ tr.eid[s] = 0;
        mark[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            mark[u] = false;

            for (auto &e : G[u]) {
                int v = e.v;
                if (dist[v] > dist[u] + e.w) {
                    dist[v] = dist[u] + e.w;
                    /* tr.fa[v] = u; */
                    tr.eid[v] = e.id;
                    if (!mark[v]) {
                        if (!q.empty() && dist[v] < dist[q[0]])
                            q.push_front(v);
                        else
                            q.push_back(v);
                        mark[v] = true;
                    }
                }
            }
        }

        return tr;
    }
};

struct DijkstraAlgorithm {
    int n;
    i64 *dist;

    DijkstraAlgorithm(int _n) : n(_n), dist(new i64[n]) {}
    ~DijkstraAlgorithm() { delete[] dist; }

    auto operator()(const Graph &G, int s) -> SPTree {
        memset(dist + 1, 0x3f, sizeof(i64) * n);
        dist[s] = 0;

        struct State {
            int u;
            i64 t;

            bool operator<(const State &z) const {
                return t > z.t;
            }
        };

        SPTree tr(n);
        priority_queue<State> q;
        /* tr.fa[s] = */ tr.eid[s] = 0;
        q.push({s, 0});
        while (!q.empty()) {
            auto _ = q.top();
            q.pop();
            int u = _.u;
            if (_.t > dist[u])
                continue;

            for (auto &e : G[u]) {
                int v = e.v;
                if (dist[v] > dist[u] + e.w) {
                    dist[v] = dist[u] + e.w;
                    /* tr.fa[v] = u; */
                    tr.eid[v] = e.id;
                    q.push({v, dist[v]});
                }
            }
        }

        return tr;
    }
};

template <typename TCallback>
struct TarjanLCA {
    struct UnionFind {
        int n;
        int *fa;

        UnionFind(int _n) : n(_n), fa(new int[n + 1]) {}
        ~UnionFind() { delete[] fa; }

        void clear() {
            memset(fa, 0, sizeof(int) * (n + 1));
        }

        int find(int u) {
            return fa[u] ? fa[u] = find(fa[u]) : u;
        }

        auto operator[](int u) -> int& {
            return fa[u];
        }
    };

    const TCallback &callback;
    UnionFind dsu;
    i64 *dist;

    TarjanLCA(int n, const TCallback &_callback)
        : callback(_callback), dsu(n), dist(new i64[n + 1]) {}
    ~TarjanLCA() { delete[] dist; }

    struct Impl {
        const Graph &G;
        const SPTree &tr;
        TarjanLCA *self;

        Impl(const Graph &_G, const SPTree &_tr, TarjanLCA *_self)
            : G(_G), tr(_tr), self(_self) {}

        void dfs(int u) {
            for (auto &e : G[u])
            if (tr.eid[e.v] == e.id) {
                int v = e.v;
                self->dist[v] = self->dist[u] + e.w;
                dfs(v);
                self->dsu[v] = u;
                self->callback(u, e, -1);
            }

            for (auto &e : G[u])
            if (tr.eid[e.v] != e.id && tr.eid[u] != e.id &&
                self->dsu[e.v]) {
                int v = e.v, p = self->dsu.find(v);
                self->callback(
                    u, e,
                    self->dist[u] + self->dist[v] - 2 * self->dist[p]
                );
            }
        }
    };

    void operator()(const Graph &G, const SPTree &tr, int s) {
        dsu.clear();
        dist[s] = 0;
        Impl(G, tr, this).dfs(s);
    }
};

struct Solver {
    static constexpr int TMAX = 5;

    typedef SPFAAlgorithm Algorithm;
    typedef i64 LengthVec[TMAX];
    typedef bool *EnableList;

    int n;
    Graph G, G0;
    Algorithm shortest;
    LengthVec *len;
    EnableList en;

    Solver(int _n, int m, const Graph &_G)
        : n(_n), G(_G), G0(_G), shortest(G.n),
          len(new LengthVec[n + 1]), en(new bool[m + 1]),
          tm(new int[n + 1]), dist(new i64[n + 1]) {
        memset(en + 1, 1, m);
        memset(tm, 0, sizeof(int) * (n + 1));

        // TODO: random
        // static random_device rd;
        // static mt19937_64 randi(rd());
        static mt19937_64 randi(19260817);

        Graph G1(n);
        // Strange if I remove the "check" variable and write the function
        // directly in "TarjanLCA"'s constructor, it results in a segmentation fault
        // on g++ or clang with -O1
        // Looks like "G1" is not correctly captured.
        auto check = [&G1](int u, const Edge &e, i64 d) {
            if (d < 0 || e.w < d)
                G1.link(u, e.v, e.w, e.id);
            else DEBUG("%d - %d (%d) removed.", u, e.v, e.w);
        };
        TarjanLCA travesal(n, check);

        for (int i = 0, s = 1; i < TMAX;
             i++, s = randi() % n + 1) {
            DEBUG("s = %d", s);
            auto tr = shortest(G, s);  // TODO: reuse "tr"

            G1.clear();
            travesal(G, tr, s);
            G = G1;

            for (int u = 1; u <= n; u++)
                len[u][i] = travesal.dist[u];
        }
    }

    ~Solver() {
        delete[] len;
        delete[] en;
        delete[] tm;
        delete[] dist;
    }

    i64 h(int u, int v) {
        i64 ret = 0;
        for (int i = 0; i < TMAX; i++)
            ret = max(ret, abs(len[u][i] - len[v][i]));
        return ret;
    }

    i64 query(int s, int t, const vector<int> disabled) {
        if (s == t)
            return 0;

        for (int v : disabled)
            en[v] = false;

        i64 ans = search(s, t);

        for (int v : disabled)
            en[v] = true;
        return ans;
    }

  private:
    int *tm;
    i64 *dist;

    i64 search(int s, int t) {
        static int cur;
        cur += 4;

        struct State {
            int u;
            i64 t;

            bool operator<(const State &z) const {
                return t > z.t;
            }
        };

        i64 ans = INF, esi = h(s, t);
        int p[] = {s, t};
        tm[s] = cur, tm[t] = cur | 1;
        dist[s] = dist[t] = 0;
        priority_queue<State> q[2];
        q[0].push({s, esi});
        q[1].push({t, esi});

        int cnt = 0;
        while (!q[0].empty() || !q[1].empty()) {
            int i;
            if (!q[0].empty() && !q[1].empty())
                i = q[0].top().t < q[1].top().t ? 0 : 1;
            else i = q[0].empty() ? 1 : 0;

            auto _ = q[i].top();
            q[i].pop();

            int u = _.u;
            if (tm[u] & 2)
                continue;
            tm[u] |= 2;

            for (auto &e : G0[u]) if (en[e.id]) {
                cnt++;

                int v = e.v;
                if (tm[v] >= cur && (tm[v] & 1) != (tm[u] & 1)) {
                    ans = min(ans, dist[u] + e.w + dist[v]);
                    DEBUG("%d - %d (%d): ans = %lld", u, v, e.w, ans);
                } else {
                    esi = dist[u] + e.w + h(v, p[i ^ 1]);
                    if (esi >= ans)
                        continue;
                    if (tm[v] < cur) {
                        tm[v] = tm[u] & 0xFFFFFFFD;
                        dist[v] = INF;
                    }
                    if (dist[v] > dist[u] + e.w) {
                        dist[v] = dist[u] + e.w;
                        DEBUG("[%d] %d → %d: %lld (%lld)", i, u, v, dist[v], esi);
                        q[i].push({v, esi});
                    }
                }
            }
        }

        fprintf(stderr, "cnt = %d\n", cnt);
        return ans;
    }
};

struct BCTree {
    // TODO
};

int main() {
    Reader read;
    int n, m;
    read(n, m);

    Graph G(n);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u, v, w);
        if (u == v)
            continue;
        G.link(u, v, w, i);
    }

    vector<int> disabled;
    Solver core(n, m, G);

    int q;
    read(q);
    while (q--) {
        int s, t, cnt;
        read(s, t, cnt);
        disabled.clear();
        disabled.reserve(cnt);
        while (cnt--) {
            int u;
            read(u);
            disabled.push_back(u);
        }

        i64 ans = core.query(s, t, disabled);
        printf("%lld\n", ans < INF ? ans : -1);
    }

    return 0;
}