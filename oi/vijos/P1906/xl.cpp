#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 200000
#define MOD 10007

typedef long long int64;

inline void two_sort(int64 a, int64 &first, int64 &second) {
    if (a > first) {
        second = first;
        first = a;
    } else if (a > second)
        second = a;
}

struct Element {
    Element(int _v) : v(_v), next(NULL) {}

    int v;
    Element *next;
};  // struct Element

static int n;
static Element *G[NMAX + 10];
static int64 weight[NMAX + 10];
static int64 first[NMAX + 10];
static int64 second[NMAX + 10];
static int64 sum[NMAX + 10];

inline void add_edge(int u, int v) {
    Element *eu = new Element(v);
    Element *ev = new Element(u);

    eu->next = G[u];
    ev->next = G[v];
    G[u] = eu;
    G[v] = ev;
}

static void initialize() {
    // scanf("%d", &n);
    n = read<int>();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = read<int>();
        v = read<int>();

        add_edge(u, v);
    }  // for

    for (int i = 1; i <= n; i++) {
        // scanf("%lld", weight + i);
        weight[i] = read<int64>();
    }  // for

    for (int u = 1; u <= n; u++) {
        for (Element *ptr = G[u]; ptr; ptr = ptr->next) {
            int v = ptr->v;

            sum[u] += weight[v];
            sum[u] %= MOD;
            two_sort(weight[v], first[u], second[u]);
        }  // for
    }      // for
}

int main() {
    initialize();

    int64 maxans = 0;
    int64 sumans = 0;
    for (int u = 1; u <= n; u++) {
        maxans = max(maxans, first[u] * second[u]);

        for (Element *ptr = G[u]; ptr; ptr = ptr->next) {
            int v = ptr->v;

            sumans += (sum[u] - weight[v]) * weight[v];
            sumans %= MOD;
        }  // for
    }      // for

    if (sumans < 0)
        sumans += MOD;

    printf("%lld %lld", maxans, sumans);

    return 0;
}  // function main
