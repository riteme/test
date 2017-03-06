// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t cur = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (cur == BUFFERSIZE) {
        cur = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }

    return buffer[cur++];
}

template <typename T>
inline T read() {
    T x = 0;
    T f = 1;
    char c = _getchar();

    while (!isdigit(c)) {
        if (c == '-')
            f = -1;
        c = _getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x * f;
}

#define NMAX 200000
#define CIRCLE_MAX 2000000

typedef long long i64;
typedef pair<i64, i64> i64Pair;

struct Vector {
    Vector() : x(0), y(0) {}
    Vector(i64 _x, i64 _y)
        : x(_x), y(_y) {}

    i64 x, y;

    friend Vector operator-(const Vector &a, const Vector &b) {
        return Vector(a.x - b.x, a.y - b.y);
    }
};

inline i64 cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

inline int area_id(const Vector &a) {
    if (0 <= a.x && 0 < a.y)
        return 1;
    if (0 < a.x && 0 >= a.y)
        return 2;
    if (0 >= a.x && 0 > a.y)
        return 3;
    return 4;
}

struct Edge {
    Edge(int _u, int _v)
        : u(_u), v(_v), dual_id(0),
          reverse_edge(NULL), next(NULL) {}

    int u, v;
    int dual_id;
    Edge *reverse_edge;
    Edge *next;
};

class HashTable {
 public:
    void insert(i64 key, i64Pair val) {
        int pos = key % MOD;
        bucket[pos].push_back(make_pair(key, val));
    }

    i64Pair find(i64 key) {
        int pos = key % MOD;
        for (size_t i = 0; i < bucket[pos].size(); i++) {
            if (bucket[pos][i].first == key)
                return bucket[pos][i].second;
        }
        
        return i64Pair(0, 0);
    }

 private:
    static const int MOD = 857539;

    typedef pair<i64, i64Pair> DataType;

    vector<DataType> bucket[MOD];
};

static int n, m, q, dual_cnt;
static Vector pos[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static vector<Edge *> D[NMAX * 4 + 10];
static HashTable val;
static bool marked[NMAX * 4 + 10];

inline void link(int u, int v) {
    Edge *e1 = new Edge(u, v);
    Edge *e2 = new Edge(v, u);
    e1->reverse_edge = e2;
    e2->reverse_edge = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

bool cmp(const Edge *a, const Edge *b) {
    Vector va = pos[a->v] - pos[a->u];
    Vector vb = pos[b->v] - pos[b->u];
    int ida = area_id(va);
    int idb = area_id(vb);

    if (ida != idb)
        return ida < idb;
    return cross(va, vb) < 0;
}

void dfs(Edge *e) {
    if (e->dual_id)
        return;
    
    // printf("%d: %d -> %d\n", dual_cnt, e->u, e->v);
    e->dual_id = dual_cnt;
    D[dual_cnt].push_back(e);
    dfs(e->reverse_edge->next);
}

inline i64 id(i64 u, i64 v) {
    return (u << 32) + v;
}

i64Pair spanning(int u) {
    marked[u] = true;

    i64 size = 0, suma = 0, suma2 = 0;
    
    if (u > 1) {
        int p = D[u][0]->u;
        for (size_t i = 1; i < D[u].size() - 1; i++) {
            Edge *e = D[u][i];
            size += cross(pos[e->u] - pos[p], pos[e->v] - pos[p]);
        }
        
        suma = size = abs(size);
        suma2 = size * size;
    }

    for (size_t i = 0; i < D[u].size(); i++) {
        Edge *e = D[u][i];
        int v = e->reverse_edge->dual_id;
        
        if (marked[v])
            continue;

        i64Pair ret = spanning(v);
        // printf("span: %d -> %d, suma = %lld, suma2 = %lld\n",
        //        u, v, ret.first, ret.second);
        val.insert(id(e->u, e->v), make_pair(-ret.first, -ret.second));
        val.insert(id(e->v, e->u), ret);
        suma += ret.first;
        suma2 += ret.second;
    }

    return make_pair(suma, suma2);
}

void initialize() {
    // scanf("%d%d%d", &n, &m, &q);
    n = read<int>();
    m = read<int>();
    q = read<int>();

    for (int i = 1; i <= n; i++) {
        // scanf("%lld%lld", &pos[i].x, &pos[i].y);
        pos[i].x = read<i64>();
        pos[i].y = read<i64>();
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = read<int>();
        v = read<int>();
        link(u, v);
    }

    for (int u = 1; u <= n; u++) {
        sort(G[u].begin(), G[u].end(), cmp);

        for (size_t i = 0; i < G[u].size(); i++) {
            G[u][i]->next = G[u][(i + 1) % G[u].size()];
        }
    }

    int p = 1;
    for (int u = 2; u <= n; u++) {
        if (pos[u].x < pos[p].x)
            p = u;
    }

    Edge *s = G[p][0];
    for (size_t i = 1; i < G[p].size(); i++) {
        Edge *e = G[p][i];
        if (cross(pos[s->v] - pos[p], pos[e->v] - pos[p]) > 0)
            s = e;
    }

    dual_cnt = 1;
    dfs(s);

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];

            if (!e->dual_id) {
                dual_cnt++;
                dfs(e);
            }
        }
    }

    spanning(1);
}

inline i64 gcd(i64 a, i64 b) {
    while (b) {
        i64 tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

static int cir[CIRCLE_MAX + 10];

int main() {
    initialize();

    i64 lastans = 0;
    while (q--) {
        int c;
        // scanf("%d", &c);
        c = read<int>();
        c = (c + lastans) % n + 1;

        for (int i = 0; i < c; i++) {
            // scanf("%d", cir + i);
            cir[i] = read<int>();
            cir[i] = (cir[i] + lastans) % n + 1;
        }

        i64 suma2 = 0, suma = 0;
        for (int i = 0; i < c; i++) {
            int u = cir[i];
            int v = cir[(i + 1) % c];
            i64Pair res = val.find(id(u, v));
            suma2 += res.second;
            suma += res.first;
        }

        suma <<= 1;
        i64 d = gcd(suma2, suma);
        suma2 /= d;
        suma /= d;
        printf("%lld %lld\n", suma2, suma);
        lastans = suma2;
    }

    return 0;
}
