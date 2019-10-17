#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 34981
#define INV2 17491
#define NMAX 300
#define QMAX 100000

struct Matrix {
    Matrix() : m11(1), m12(0), m21(0), m22(1) {}
    Matrix(int _m11, int _m12, int _m21, int _m22)
        : m11(_m11), m12(_m12), m21(_m21), m22(_m22) {}

    int m11, m12, m21, m22;

    Matrix operator*(const Matrix &z) const {
        Matrix r;
        memset(&r, 0, sizeof(r));
        r.m11 = (m11 * z.m11 + m12 * z.m21) % MOD;
        r.m12 = (m11 * z.m12 + m12 * z.m22) % MOD;
        r.m21 = (m21 * z.m11 + m22 * z.m21) % MOD;
        r.m22 = (m21 * z.m12 + m22 * z.m22) % MOD;
        return r;
    }

    Matrix &operator*=(const Matrix &z) {
        Matrix r;
        memset(&r, 0, sizeof(r));
        r.m11 = (z.m11 * m11 + z.m12 * m21) % MOD;
        r.m12 = (z.m11 * m12 + z.m12 * m22) % MOD;
        r.m21 = (z.m21 * m11 + z.m22 * m21) % MOD;
        r.m22 = (z.m21 * m12 + z.m22 * m22) % MOD;
        memcpy(this, &r, sizeof(r));
        return *this;
    }
};

static int n, m, q;
static char M0[NMAX + 10][NMAX + 10];
static char M[NMAX + 10][NMAX + 10];
static char op[QMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", M0[i] + 1);
    scanf("%s", op + 1);
    q = strlen(op + 1);

    Matrix T;
    Matrix VF(1, 0, 0, -1),
           HF(-1, 0, 0, 1),
           T1(0, 1, 1, 0),
           T2(0, -1, -1, 0),
           CW(0, 1, -1, 0),
           CCW(0, -1, 1, 0);

    bool rev = false;
    for (int i = 1; i <= q; i++) {
        switch (op[i]) {
            case '1': T *= T1, rev ^= 1; break;
            case '2': T *= T2, rev ^= 1; break;
            case 'H': T *= HF; break;
            case 'V': T *= VF; break;
            case 'A': T *= CW, rev ^= 1; break;
            case 'B': T *= CW * CW; break;
            case 'C': T *= CW * CW * CW, rev ^= 1; break;
            case 'X': T *= CCW, rev ^= 1; break;
            case 'Y': T *= CCW * CCW; break;
            case 'Z': T *= CCW * CCW * CCW, rev ^= 1; break;
        }
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        int x0 = (i - (n + 1) * INV2) % MOD;
        int y0 = (j - (m + 1) * INV2) % MOD;
        int x = (T.m11 * x0 + T.m12 * y0) % MOD;
        int y = (T.m21 * x0 + T.m22 * y0) % MOD;
        int px = (x + ((rev ? m : n) + 1) * INV2) % MOD;
        int py = (y + ((rev ? n : m) + 1) * INV2) % MOD;
        if (px < 0) px += MOD;
        if (py < 0) py += MOD;
        M[px][py] = M0[i][j];
    }

    if (rev) swap(n, m);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++)
        printf("%s\n", M[i] + 1);

    return 0;
}
