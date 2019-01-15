/**
 * Problem: island
 * Correct solution (must be OK).
 * Author: stgatilov
 * Chooses one of two DP solutions, whichever is faster.
 * Time: O(1.4^N * N)    (x N for popcount)
 */

//#pragma comment(linker, "/STACK:20000000")
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <unordered_set>
#include <cinttypes>
#include <array>

using namespace std;
typedef long long int64;
#ifdef HOME
    #define E(c) cerr<<#c
    #define Eo(x) cerr<<#x<<" = "<<(x)<<endl
    #define Ef(...) fprintf(stderr, __VA_ARGS__)
#else
    #define E(c) ((void)0)
    #define Eo(x) ((void)0)
    #define Ef(...) ((void)0)
#endif

int countbits(int64 x) {
    int res = 0;
    while (x) {
        res++;
        x = x & (x-1);
    }
    return res;
}

const int MAXN = 52;
const int MAXB = 22;

int n, m;
int edges[MAXN][MAXN];

int r, c;
int rows[MAXN], cols[MAXN];
int matr[MAXN][MAXN];

int ans = -1;
int sol[MAXN];

int64 all[MAXN], fr[MAXN];
void Prepare() {
    for (int i = 0; i < r; i++) {
        all[i] = fr[i] = 0;
        for (int j = 0; j < c; j++) {
            all[i] |= int64(matr[i][j] != 0) << j;
            fr[i] |= int64(matr[i][j] > 0) << j;
        }
    }
}

int res[1<<MAXB], addRow[1<<MAXB], prevSet[1<<MAXB];
void SolveCols() {
    memset(res, -63, sizeof(res));
    memset(addRow, -1, sizeof(addRow));
    memset(prevSet, -1, sizeof(prevSet));
    res[0] = 0;
    int bestS = -1;
    for (int s = 0; s < (1<<c); s++) {
        for (int i = 0; i < r; i++) {
            int ns = s | all[i];
            int64 add = (~s) & fr[i];
            int nres = res[s] + countbits(add);
            if (res[ns] < nres) {
                res[ns] = nres;
                addRow[ns] = i;
                prevSet[ns] = s;
            }
        }
        if (ans < res[s]) {
            ans = res[s];
            bestS = s;
        }
    }

    int s = bestS;
    int k = 0;
    while (s > 0) {
        sol[k++] = addRow[s];
        s = prevSet[s];
    }
    reverse(sol, sol + k);
    for (int i = 0; i < r; i++)
        if (!count(sol, sol + k, i))
            sol[k++] = i;
    assert(k == r);
}

void SolveRows() {
    memset(res, -63, sizeof(res));
    memset(addRow, -1, sizeof(addRow));
    res[0] = 0;
    for (int s = 0; s < (1<<r); s++) {
        int64 mask = 0;
        for (int i = 0; i < r; i++) if (s & (1<<i))
            mask |= all[i];
        for (int i = 0; i < r; i++) if (!(s & (1<<i))) {
            int ns = s + (1<<i);
            int64 add = fr[i] & (~mask);
            int nres = res[s] + countbits(add);
            if (res[ns] < nres) {
                res[ns] = nres;
                addRow[ns] = i;
            }
        }
    }

    int s = (1<<r) - 1;
    ans = res[s];
    for (int i = 0; i < r; i++) {
        int f = addRow[s];
        sol[i] = f;
        s -= (1<<f);
    }
    reverse(sol, sol + r);
}

int main(int argc, char **argv) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        a--;  b--;
        t = (t == 0 ? 1 : -1);
        edges[a][b] = t;
        edges[b][a] = t;
    }

    for (int i = 1; i < n; i++) {
        if (edges[i][0])
            rows[r++] = i;
        else {
            for (int j = 1; j < n; j++) if (edges[i][j] && edges[j][0]) {
                cols[c++] = i;
                break;
            }
        }
    }
    for (int i = 0; i < r; i++) Ef("%d ", rows[i]); Ef("\n");
    for (int j = 0; j < c; j++) Ef("%d ", cols[j]); Ef("\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int a = rows[i], b = cols[j];
            int q = edges[b][a] * edges[a][0];
            matr[i][j] = q;
            Ef("%c ", q == 0 ? '0' : q < 0 ? '-' : '+');
        }
        Ef("\n");
    }

    Prepare();
    if (r < c)
        SolveRows();
    else
        SolveCols();
    Eo(ans);

    for (int i = 0; i < r; i++)
        if (edges[0][rows[i]] > 0)
            ans++;

    printf("%0.15lf\n", ans / double(n-1));
    for (int i = 0; i < r; i++) {
        if (i) printf(" ");
        printf("%d", rows[sol[i]] + 1);
    }
    printf("\n");

    return 0;
}
