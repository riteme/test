#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 3000

typedef long long i64;

static int n, m;
static char mat[NMAX + 10][NMAX + 10];
static int L[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", mat[i] + 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (mat[i][j] == '0') L[i][j] = 0;
        else L[i][j] = L[i][j - 1] + 1;
    }
    i64 ans = 0;
    for (int j = 1; j <= m; j++) {
        deque<int> stk;
        stk.push_front(0);
        int p0 = 0;
        for (int i = 1; i <= n + 1; i++) {
            while (!stk.empty() && L[stk[0]][j] >= L[i][j]) {
                if (stk.size() > 1 && L[stk[0]][j] > L[i][j] && stk[1] < p0) {
                    //printf("%d, %d: %d, p0 = %d\n", i, j, stk[0], p0);
                    ans++;
                }
                stk.pop_front();
            }
            stk.push_front(i);
            if (mat[i][j + 1] != '1') p0 = i;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
