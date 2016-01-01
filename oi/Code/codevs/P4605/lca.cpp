// LCA

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000

typedef int ntype;

void initialize();
void quit();

static ntype n, m;
static ntype M;
static ntype root;
static ntype last;
static vector<ntype> T[NMAX + 1];
static ntype depth[NMAX + 1];
static ntype f[NMAX + 1][21];

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }  // while

    return x;
}

void extend_f(const ntype i, const ntype j);
void extend_depth(const ntype x);
ntype lca(const ntype u, const ntype v);

int main() {
    initialize();

    for (int cnt = 0; cnt < m; cnt++) {
        ntype x = read(), y = read();

        if (x == y)
            last ^= x;
        else {
            ntype rx = x ^ last;
            ntype ry = y ^ last;

            last = lca(rx, ry);
        }

        printf("%d\n", last);
    }  // for

    quit();
    return 0;
}  // function main

void extend_f(const ntype iMax, const ntype jMax) {
    for (ntype j = 1; j <= jMax; j++) {
        for (ntype i = 1; i <= iMax; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }  // for
    }      // for
}

void extend_depth(const ntype x) {
    queue<ntype> q;
    q.push(x);

    while (!q.empty()) {
        ntype u = q.front();
        q.pop();

        for (ntype i = 0; i < T[u].size(); i++) {
            ntype v = T[u][i];

            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }  // while
}

ntype lca(ntype u, ntype v) {
    // 保持u处于更深的地方
    if (depth[u] < depth[v]) swap(u, v);

    ntype dist = depth[u] - depth[v];

    // 调整u与v处于同一高度
    for (ntype i = 0; i < M; i++)
        // ***IMPORTANT***
        // 此处尝试将u和v的距离缩短为0
        // 即u上升的距离为dist
        //
        // 设一个数可以表示为一个二进制t
        // 则sum((2 ** k) * t[k]) = t
        // 即一位一位地补全t的二进制
        // 例如，要将某数的第k位二进制由0设为1
        // 只需n = n + 2 ** k
        // 2 ** k = 1 << k
        //
        // 下面的(1 << i) & dist是判断dist
        // 的第i位是否为1
        // 如果为一，则u因上升2 ** i个距离
        if ((1 << i) & dist) u = f[u][i];

    // depth[u] == depth[v]
    // assert(depth[u] == depth[v]); --> OK
    if (u == v) return u;

    for (ntype i = M - 1; i >= 0; i--) {
        // 逼近LCA
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }

    // u, v处在同一高度，其父节点为LCA
    return f[u][0];
}

void initialize() {
    n = read();
    for (int i = 1; i <= n; i++) {
        f[i][0] = read();

        if (f[i][0] == 0)
            root = i;
        else
            T[f[i][0]].push_back(i);
    }  // for

    depth[root] = 0;
    extend_depth(root);

    M = 20;
    extend_f(n, M);

    m = read();
    last = 0;
}

void quit() {}
