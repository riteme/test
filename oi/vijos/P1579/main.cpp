#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define NMAX 20000

typedef long long ntype;

struct Edge {
    ntype u;
    ntype v;
    ntype w;
};  // struct Edge

static ntype n;
static ntype total;
static Edge edges[NMAX + 10];
static Edge *edges_ptr[NMAX + 10];
static ntype size[NMAX + 10];
static ntype set[NMAX + 10];

inline void make_set() {
    for (ntype i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline ntype find_set(ntype x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(ntype x, ntype y) {
    x = find_set(x);
    y = find_set(y);

    set[x] = y;
    size[y] += size[x];
}

bool compare(const Edge *a, const Edge *b) {
    return a->w < b->w;
}

void initialize() {
    cin >> n;

    for (ntype i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges_ptr[i] = &edges[i];
    }  // for

    sort(edges_ptr + 1, edges_ptr + n, compare);

    for (ntype i = 1; i <= n; i++) {
        size[i] = 1;
    }  // for

    total = 0;
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    make_set();

    ntype index = 1;
    while (index < n) {
        ntype u = edges_ptr[index]->u;
        ntype v = edges_ptr[index]->v;
        ntype iu = find_set(u);
        ntype iv = find_set(v);
        ntype nw = edges_ptr[index]->w + 1;
        // cout << "u = " << u << ", v = " << v << ", size[u] = " << size[iu]
        // << ", size[v] = " << size[v] << endl;

        total += nw * (size[iu] * size[iv] - 1) + nw - 1;

        union_set(u, v);
        index++;
    }  // while

    cout << total;
    return 0;
}  // function main
