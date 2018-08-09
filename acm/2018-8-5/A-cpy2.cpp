#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define DMAX 200
#define MMAX 2000000

typedef bitset<NMAX> Bits;

struct Edge {
	int u, v, d;
};

static int fa[DMAX + 10][NMAX + 10], L[MMAX + 10], R[MMAX + 10];
static Edge e[MMAX + 10];
static bool no[NMAX + 10][NMAX + 10];
static bool used[MMAX + 10];
static Bits nodes[MMAX + 10];

inline int find(int d, int x) {
	return fa[d][x] > 0 ? fa[d][x] = find(d, fa[d][x]) : x;
}

static int d, n, m;
static int pre[MMAX + 10];
static int A[NMAX + 10], acnt;

int main() {
	scanf("%d%d%d", &d, &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		e[i] = {u - 1, v - 1, k};
		int idu = find(k, u), idv = find(k, v);
		if (idu != idv) {
            if (fa[k][idu]) nodes[i] |= nodes[-fa[k][idu]];
            else nodes[i][u - 1] = true;
            if (fa[k][idv]) nodes[i] |= nodes[-fa[k][idv]];
            else nodes[i][v - 1] = true;
            L[i] = -fa[k][idu];
            R[i] = -fa[k][idv];
			fa[k][idu] = idv;
            fa[k][idv] = -i;
			used[i] = true;
		}
	}

	int om = m;
	for (int i = 1; i <= d; i++) {
		acnt = 0;
		for (int j = 1; j <= n; j++)
			A[j] = find(i, j);
		sort(A + 1, A + n + 1);
		acnt = unique(A + 1, A + n + 1) - A - 1;

		for (int j = 1; j < acnt; j++) {
			int u = A[j], v = A[j + 1];
			e[++m] = {u - 1, v - 1, i};
            int idu = find(i, u), idv = find(i, v);
            if (fa[i][idu]) nodes[m] |= nodes[-fa[i][idu]];
            else nodes[m][u - 1] = true;
            if (fa[i][idv]) nodes[m] |= nodes[-fa[i][idv]];
            else nodes[m][v - 1] = true;
            L[m] = -fa[i][idu];
            R[m] = -fa[i][idv];
            fa[i][idu] = idv;
            fa[i][idv] = -m;
			used[m] = true;
		}
	}

	for (int i = m; i >= 1; i--) {
		if (!used[i]) continue;
		int u = e[i].u, v = e[i].v;
        acnt = 0;
        if (L[i]) {
            for (int j = 0; j < n; j++)
                if (nodes[L[i]][j]) A[acnt++] = j;
        } else A[acnt++] = u;
        if (R[i]) {
            for (int j = 0; j < n; j++) {
                if (!nodes[R[i]][j]) continue;
                for (int k = 0; k < acnt; k++) {
                    if (no[j][A[k]]) continue;
                    pre[i]++;
                    no[j][A[k]] = no[A[k]][j] = true;
                }
            }
        } else {
            for (int j = 0; j < acnt; j++) {
                if (no[v][A[j]]) continue;
                pre[i]++;
                no[v][A[j]] = no[A[j]][v] = true;
            }
        }
	}

	for (int i = 1; i <= om; i++) {
		pre[i] += pre[i - 1];
		printf("%d\n", pre[i] * 2 + n);
	}

	return 0;
}
