#include <cassert>
#include <cstring>
#include <climits>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 20
#define SIZE (LOGN / 2)
#define TYPES (1 << (SIZE - 1))

static int n, q;
static int fa[NMAX];
static vector<int> ch[NMAX];
static int dep[NMAX], in[NMAX];
static int cur, hb[NMAX * 2], seq[NMAX * 2];
static int st[LOGN + 1][NMAX * 2], type[NMAX];
static int block[TYPES][SIZE][SIZE];

void dfs(int u) {
    in[u] = cur;
    seq[cur++] = u;

    for (int v : ch[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        seq[cur++] = u;
    }  // foreach in ch[u]
}

bool cmp(const int x, const int y) {
    if (x < 0)
        return false;
    if (y < 0)
        return true;
    return dep[seq[x]] < dep[seq[y]];
}

void initialize_st() {
    dep[0] = INT_MAX;

    for (int s = 0; s < TYPES; s++) {
        for (int l = 0; l < SIZE; l++) {
            int p = 0, maxp = 0;
            block[s][l][l] = l;
            for (int r = l + 1; r < SIZE; r++) {
                p += (s >> (r - 1)) & 1 ? 1 : -1;
                if (p < maxp) {
                    maxp = p;
                    block[s][l][r] = r;
                } else
                    block[s][l][r] = block[s][l][r - 1];
            }  // for
        }      // for
    }          // for

    int pos = cur;
    cur = 0;
    for (int i = 0; i < pos; i += SIZE, cur++) {
        st[0][cur] = i;
        for (int j = i + 1; j < i + SIZE && j < pos; j++) {
            if (cmp(j, st[0][cur]))
                st[0][cur] = j;
            if (cmp(j - 1, j))
                type[cur] |= 1 << (j - i - 1);
        }  // for
    }      // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 0; i < cur; i++) {
            st[j][i] = min(
                st[j - 1][i],
                i + (1 << (j - 1)) < cur ? st[j - 1][i + (1 << (j - 1))] : -1,
                cmp);
        }  // for
    }      // for
}

void initialize() {
    ios::sync_with_stdio(false);

    cin >> n >> q;
    for (int u = 2; u <= n; u++) {
        cin >> fa[u];
        ch[fa[u]].push_back(u);
    }

    dfs(1);
    initialize_st();

    hb[1] = 0;
    for (int i = 2; i <= n * 2; i++) {
        hb[i] = hb[i >> 1] + 1;
    }  // for
}

int lca(int u, int v) {
    if (in[u] > in[v])
        swap(u, v);

    int ret = -1;
    // int l = u, r = v, ld = l / SIZE, rd = r / SIZE;
    int l = in[u], r = in[v], ld = l / SIZE, rd = r / SIZE;

    if (ld + 1 <= rd - 1) {
        int k = hb[rd - ld - 1];
        ret = min(st[k][ld + 1], st[k][rd - (1 << k)], cmp);
    }

    if (ld == rd)
        ret = min(ret, ld * SIZE + block[type[ld]][l % SIZE][r % SIZE], cmp);
    else {
        ret = min(ret, ld * SIZE + block[type[ld]][l % SIZE][SIZE - 1], cmp);
        ret = min(ret, rd * SIZE + block[type[rd]][0][r % SIZE], cmp);
    }

    return seq[ret];
}

int main() {
    initialize();

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
