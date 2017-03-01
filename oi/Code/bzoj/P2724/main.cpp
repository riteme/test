/**
 * 好机智的想法，首先随便选一个数写在左上角，
 * 然后每次向右就乘以3，向下就乘以2
 * 例如1：
 * 1  3  6  27 ...
 * 2  6 18  54 ...
 * 4 12 36 108 ...
 * 8 ...
 * 然后对于这些数，合法的方案即在矩阵中没有相邻元素
 * 于是可以状压DP
 * 有一些数可能并没有出现，于是需要将这些数继续执行上面的过程
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define LOGN 17
#define MOD 1000000001

static int n;
static int w, h;
static int mat[LOGN + 10];
static bool marked[NMAX + 10];

void fill(int x) {
    w = h = 0;
    memset(mat, 0, sizeof(mat));
    for (int u = x; u <= n; w++, u *= 2) {
        mat[w] = 1;
        marked[u] = true;
        for (int v = u * 3, i = 1; v <= n; i++, v *= 3) {
            mat[w] |= 1 << i;
            marked[v] = true;
            h = max(h, i);
        }
    }
}

static i64 initial[NMAX * 2 + 10];
static i64 dp1[NMAX * 2 + 10];
static i64 dp2[NMAX * 2 + 10];

i64 dp() {
    int size = 1 << (h + 1);
    memcpy(dp1, initial, sizeof(i64) * size);
    
    i64 *cur = dp2, *last = dp1;
    for (int i = 1; i < w; i++) {
        memset(cur, 0, sizeof(i64) * size);
        for (int s1 = 0; s1 < size; s1++) {
            if ((s1 & (s1 << 1)) || (s1 & (s1 >> 1)))
                continue;
            if ((s1 | mat[i]) > mat[i])
                continue;

            for (int s2 = 0; s2 < size; s2++) {
                if (s1 & s2)
                    continue;

                cur[s1] = (cur[s1] + last[s2]) % MOD;
            }
        }

        swap(cur, last);
    }

    i64 ret = 0;
    for (int s = 0; s < size; s++) {
        ret = (ret + last[s]) % MOD;
    }

    return ret;
}

int main() {
    scanf("%d", &n);

    for (int s = 0; s < (1 << LOGN); s++) {
        initial[s] = (s & (s >> 1)) || (s & (s << 1)) ? 0 : 1;
    }

    i64 answer = 1;
    for (int i = 1; i <= n; i++) {
        if (marked[i])
            continue;
        fill(i);
        answer = answer * dp() % MOD;
    }

    printf("%lld\n", answer);

    return 0;
}
