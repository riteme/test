#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 1510

typedef bitset<NMAX> vec;

static int n, K;
static int a[NMAX + 10][NMAX + 10];
static int sgn[NMAX + 10];
static bool has[NMAX + 10];
static vec b[NMAX + 10];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= K; j++)
        scanf("%d", &a[i][j]);

    bool ok = true;
    for (int i = 1; ok && i <= n; i++) {
        vec v;
        int s = 1;
        for (int k = 1; k <= K; k++)
            v[k] = abs(a[i][k]) & 1;
        bool sel = false;
        for (int k = 1; k <= K; k++) if (v[k]) {
            if (has[k]) {
                s ^= sgn[k];
                v ^= b[k];
            } else {
                sel = has[k] = true;
                sgn[k] = s;
                b[k] = v;
                break;
            }
        }
        if (!sel && s) ok = false;
    }
    puts(ok ? "Yes" : "No");

    return 0;
}
