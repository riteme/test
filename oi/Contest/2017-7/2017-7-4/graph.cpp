#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 2000

typedef long long i64;

#define rep(x, l, r) for (int x = l; x <= r; x++)

static int n, m, P;
static int u[NMAX + 10], v[NMAX + 10];
static i64 A[NMAX + 10][NMAX + 10];
static i64 B[NMAX + 10][NMAX + 10];
static i64 C[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &P);

    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d%d%d", u + i, v + i, &a, &b);

        A[u[i]][v[i]] = a;
        A[v[i]][u[i]] = -a;
        B[u[i]][v[i]] = B[v[i]][u[i]] = b;
    }
}

bool check() {
    for (int i = 1; i <= n; i++) {
        i64 s = 0;
        for (int j = 1; j <= n; j++) {
            s = (s + C[i][j]) % P;
        }

        if (s)
            return false;
    }

    return ((A[1][2] + A[2][3] + A[3][1]) % P + P) % P ==
           ((B[1][2] * C[1][2] + B[2][3] * C[2][3] + B[3][1] * C[3][1]) % P + P) % P;
}

int main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    initialize();

    if (n == 3 && m == 3) {
        rep(x, 0, P - 1) rep(y, 0, P - 1) rep(z, 0, P - 1) {
            C[u[1]][v[1]] = x;
            C[v[1]][u[1]] = -x;
            C[u[2]][v[2]] = y;
            C[v[2]][u[2]] = -y;
            C[u[3]][v[3]] = z;
            C[v[3]][u[3]] = -z;
            if (check()) {
                for (int i = 1; i <= m; i++) {
                    printf("%lld\n", C[u[i]][v[i]]);
                }
                return 0;
            }
        }
    }

    return 0;
}
