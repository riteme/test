#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5
#define MOD 1000000007

typedef long long i64;

static int n, q;
static int seq[NMAX + 10][NMAX + 10];
static i64 E[NMAX + 10];

void dfs(int pos) {
    if (pos == q) {
        for (int i = 1; i <= n; i++) {
            E[i] += seq[pos][i];
            E[i] %= MOD;
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            memcpy(seq[pos + 1], seq[pos], sizeof(seq[0]));
            int val = 0;
            for (int k = i; k <= j; k++) {
                val = max(val, seq[pos][k]);
            }

            for (int k = i; k <= j; k++) {
                seq[pos + 1][k] = val;
            }

            dfs(pos + 1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &seq[0][i]);
    }

    dfs(0);

    for (int i = 1; i <= n; i++) {
        printf("%lld ", E[i]);
    }
    printf("\n");

    return 0;
}
