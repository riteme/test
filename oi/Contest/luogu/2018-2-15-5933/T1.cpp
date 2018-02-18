// luogu-judger-enable-o2
// #pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

// --- FFT ---
template <i64 maxn, i64 proot, i64 mod> struct polynomial {
    i64 Inv[maxn], Fac[maxn], Ifac[maxn], inv2, *poly[maxn << 2], *poly2[maxn << 2], len[maxn << 2];

    inline i64 pow_mod(i64 x, i64 n) {
        i64 y = 1;
        while(n) {
            if(n & 1) {
                y = (long long) y * x % mod;
            }
            x = (long long) x * x % mod;
            n >>= 1;
        }
        return y;
    }

    polynomial() {
        inv2 = mod + 1 >> 1;
        int n = maxn - 1;
        Fac[0] = 1;
        for (int i = 1; i <= n; ++i) {
            Fac[i] = (long long) i * Fac[i - 1] % mod;
        }
        Ifac[n] = pow_mod(Fac[n], mod - 2);
        for (int i = n; i; --i) {
            Ifac[i - 1] = (long long) i * Ifac[i] % mod;
        }
        for (int i = 1; i <= n; ++i) {
            Inv[i] = (long long) Fac[i - 1] * Ifac[i] % mod;
        }
        return;
    }

    inline i64 lowbit(i64 n) {
        return n & (-n);
    }

    inline int getpw2(int n) {
        while(__builtin_popcount(n) != 1) {
            n += lowbit(n);
        }
        return n;
    }

    inline void dft(int n, i64 *a, bool rev) {
        for (int i = 0, j = 0; i < n; ++i) {
            if(i < j) {
                std::swap(a[i], a[j]);
            }
            for (int k = n >> 1; (j ^= k) < k; k >>= 1);
        }
        i64 *w = new i64[n];
        w[0] = 1;
        for (int hl = 1, l = 2; l <= n; hl = l, l <<= 1) {
            i64 wn = pow_mod(proot, (mod - 1) / l);
            if(rev) {
                wn = pow_mod(wn, mod - 2);
            }
            for (register i64 i = hl - 1, *W = w + i; ~i; --i, --W) {
                W[i] = *W;
                W[i + 1] = (long long) *W * wn % mod;
            }
            for (int i = 0; i < n; i += l) {
                for (register i64 j = 0, *W = w, *b = a + i, x; j < hl; ++j, ++W, ++b) {
                    x = (long long) b[hl] * *W % mod;
                    b[hl] = (*b - x) % mod;
                    *b = (*b + x) % mod;
                }
            }
        }
        if(rev) {
            i64 inv = pow_mod(n, mod - 2);
            for (int i = 0; i < n; ++i) {
                a[i] = (long long) inv * a[i] % mod;
            }
        }
        delete w;
        return;
    }

    inline void cpy(int N, i64 *A, int n, i64 *a) {
        memcpy(A, a, sizeof(i64) * n);
        memset(A + n, 0, sizeof(i64) * (N - n));
        return;
    }

    inline void mul(int n, i64 *a, int m, i64 *b, i64 *c) {
        i64 N = getpw2(n + m - 1), *A = new i64[N], *B = new i64[N];
        cpy(N, A, n, a);
        cpy(N, B, m, b);
        dft(N, A, 0);
        dft(N, B, 0);
        for (register int i = 0; i < N; ++i) {
            A[i] = (long long) A[i] * B[i] % mod;
        }
        dft(N, A, 1);
        memcpy(c, A, sizeof(i64) * (n + m - 1));
        delete A;
        delete B;
        return;
    }

    inline void add_mul(int n, i64 *a, int m, i64 *b, i64 *c) {
        i64 N = getpw2(n + m - 1), *A = new i64[N], *B = new i64[N];
        cpy(N, A, n, a);
        cpy(N, B, m, b);
        dft(N, A, 0);
        dft(N, B, 0);
        for (register int i = 0; i < N; ++i) {
            A[i] = (long long) A[i] * B[i] % mod;
        }
        dft(N, A, 1);
        for (int i = 0; i < n + m - 1; ++i) {
            c[i] = (c[i] + A[i]) % mod;
        }
        delete A;
        delete B;
        return;
    }

    inline void inv(int n, i64 *a, i64 *b) {
        i64 N = getpw2(n), *A = new i64[N], *B = new i64[N << 1], *C = new i64[N << 1];
        cpy(N, A, n, a);
        memset(B, 0, sizeof(i64) * (N << 1));
        B[0] = pow_mod(A[0], mod - 2);
        for (int hl = 1, l = 2, l2 = 4; l <= N; hl = l, l = l2, l2 <<= 1) {
            memcpy(C, A, sizeof(i64) * l);
            memset(C + l, 0, sizeof(i64) * l);
            dft(l2, B, 0);
            dft(l2, C, 0);
            for (register int i = 0; i < l2; ++i) {
                B[i] = (2 - (long long) C[i] * B[i]) % mod * B[i] % mod;
            }
            dft(l2, B, 1);
            memset(B + l, 0, sizeof(i64) * l);
        }
        memcpy(b, B, sizeof(i64) * n);
        delete A;
        delete B;
        delete C;
        return;
    }

    inline void sqrt_1(int n, i64 *a, i64 *b) {
        i64 N = getpw2(n), *A = new i64[N], *B = new i64[N], *C = new i64[N << 1], *D = new i64[N << 1];
        cpy(N, A, n, a);
        memset(B, 0, sizeof(i64) * N);
        B[0] = 1;
        for (int hl = 1, l = 2, l2 = 4; l <= N; hl = l, l = l2, l2 <<= 1) {
            inv(l, B, C);
            memset(C + l, 0, sizeof(i64) * l);
            memcpy(D, A, sizeof(i64) * l);
            memset(D + l, 0, sizeof(i64) * l);
            dft(l2, C, 0);
            dft(l2, D, 0);
            for (register int i = 0; i < l2; ++i) {
                C[i] = (long long) C[i] * D[i] % mod * inv2 % mod;
            }
            dft(l2, C, 1);
            for (register int i = 0; i < l; ++i) {
                B[i] = ((long long) B[i] * inv2 + C[i]) % mod;
            }
        }
        memcpy(b, B, sizeof(i64) * n);
        delete A;
        delete B;
        delete C;
        delete D;
        return;
    }

    inline void der(int n, i64 *a, i64 *b) {
        for (int i = 0; i < n - 1; ++i) {
            b[i] = (long long) a[i + 1] * (i + 1) % mod;
        }
        return;
    }

    inline void ing(int n, i64 *a, i64 *b) {
        for (int i = n; i; --i) {
            b[i] = (long long) a[i - 1] * Inv[i] % mod;
        }
        b[0] = 0;
        return;
    }

    inline void log(int n, i64 *a, i64 *b) {
        i64 *A = new i64[n], *B = new i64[n], *C = new i64[n << 1];
        memcpy(A, a, sizeof(i64) * n);
        inv(n, A, B);
        der(n, A, A);
        mul(n, A, n, B, C);
        ing(n - 1, C, b);
        delete A;
        delete B;
        delete C;
        return;
    }

    inline void exp(int n, i64 *a, i64 *b) {
        i64 N = getpw2(n), *A = new i64[N], *B = new i64[N << 1], *C = new i64[N << 1];
        cpy(N, A, n, a);
        memset(B, 0, sizeof(i64) * (N << 1));
        B[0] = 1;
        for (int hl = 1, l = 2, l2 = 4; l <= N; hl = l, l = l2, l2 <<= 1) {
            log(l, B, C);
            for (register int i = 0; i < l; ++i) {
                C[i] = (A[i] - C[i]) % mod;
            }
            ++C[0];
            memset(C + l, 0, sizeof(i64) * l);
            dft(l2, C, 0);
            dft(l2, B, 0);
            for (register int i = 0; i < l2; ++i) {
                B[i] = (long long) B[i] * C[i] % mod;
            }
            dft(l2, B, 1);
            memset(B + l, 0, sizeof(i64) * l);
        }
        memcpy(b, B, sizeof(i64) * n);
        delete A;
        delete B;
        delete C;
        return;
    }

    inline void rev(int n, i64 *a) {
        for (int i = 0, j = n - 1; j > i; ++i, --j) {
            std::swap(a[i], a[j]);
        }
        return;
    }

    inline void div(int n, i64 *a, int m, i64 *b, i64 *d, i64 *r) {
        if(n < m) {
            memcpy(r, a, sizeof(i64) * n);
            return;
        }
        int N = getpw2(n), k = n - m + 1, K = getpw2(k);
        static i64 A[maxn], B[maxn], C[maxn], D[maxn];
        cpy(N, A, n, a);
        cpy(N, B, m, b);
        rev(n, A);
        rev(m, B);
        inv(K, B, C);
        mul(k, A, k, C, D);
        rev(k, D);
        rev(n, A);
        rev(m, B);
        mul(m, B, k, D, C);
        for (int i = 0; i < n; ++i) {
            B[i] = (A[i] - C[i]) % mod;
        }
        memcpy(d, D, sizeof(i64) * k);
        memcpy(r, B, sizeof(i64) * (m - 1));
        return;
    }

    inline void pow(int n, i64 *a, int N, i64 *b) {
        memset(b, 0, sizeof(i64) * n);
        if(!N) {
            b[0] = 1;
            return;
        }
        int i = 0;
        while(i < n && !a[i]) {
            ++i;
        }
        if(i == n) {
            return;
        }
        i64 *A = new i64[n];
        memset(A, 0, sizeof(i64) * n);
        for (int j = i; j < n; ++j) {
            A[j - i] = a[j];
        }
        i64 t = A[0], it = pow_mod(t, mod - 2);
        for (int j = 0; j < n; ++j) {
            A[j] = (long long) A[j] * it % mod;
        }
        log(n, A, A);
        for (int j = 0; j < n; ++j) {
            A[j] = (long long) A[j] * N % mod;
        }
        exp(n, A, A);
        i64 base = i * N;
        t = pow_mod(t, N);
        for (int j = 0; j + base < n; ++j) {
            b[j + base] = (long long) A[j] * t % mod;
        }
        delete A;
        return;
    }

    inline i64 bf_eval(int n, i64 *a, i64 x) {
        i64 y = 0;
        for (int i = n - 1; ~i; --i) {
            y = ((long long) y * x + a[i]) % mod;
        }
        return y;
    }

    inline void eval_init(int l, int r, i64 k, i64 *x) {
        if(l == r) {
            poly[k] = new i64[2];
            poly[k][0] = -x[l];
            poly[k][1] = 1;
            return;
        }
        int mid = l + r >> 1;
        eval_init(l, mid, k << 1, x);
        eval_init(mid + 1, r, (k << 1) | 1, x);
        poly[k] = new i64[r - l + 2];
        mul(mid - l + 2, poly[k << 1], r - (mid + 1) + 2, poly[(k << 1) | 1], poly[k]);
        return;
    }

    inline void eval(int n, i64 *a, int l, int r, i64 k, i64 *x, i64 *y) {
        if((long long) n * (r - l + 1) <= 20000 || n <= 10 || (r - l + 1) <= 10) {
            for (int i = l; i <= r; ++i) {
                y[i] = bf_eval(n, a, x[i]);
            }
            return;
        }
        int mid = l + r >> 1;
        i64 *b = new i64[n], *c = new i64[n], *t = new i64[n];
        memset(b, 0, sizeof(i64) * n);
        memset(c, 0, sizeof(i64) * n);
        div(n, a, mid - l + 2, poly[k << 1], t, b);
        div(n, a, r - (mid + 1) + 2, poly[(k << 1) | 1], t, c);
        delete t;
        int m = n;
        while(m && !b[m - 1]) {
            --m;
        }
        eval(m, b, l, mid, k << 1, x, y);
        delete b;
        m = n;
        while(m && !c[m - 1]) {
            --m;
        }
        eval(m, c, mid + 1, r, (k << 1) | 1, x, y);
        delete c;
        return;
    }

    inline void eval_del(int l, int r, i64 k) {
        delete poly[k];
        if(l == r) {
            return;
        }
        int mid = l + r >> 1;
        eval_del(l, mid, k << 1);
        eval_del(mid + 1, r, (k << 1) | 1);
        return;
    }

    inline void eval(int n, i64 *a, int m, i64 *x, i64 *y) {
        eval_init(0, m - 1, 1, x);
        eval(n, a, 0, m - 1, 1, x, y);
        eval_del(0, m - 1, 1);
        return;
    }

    inline void inter(int l, int r, i64 k, i64 *x, i64 *y) {
        if(l == r) {
            poly2[k] = new i64[len[k] = 1];
            poly2[k][0] = y[l];
            return;
        }
        int mid = l + r >> 1, lc = k << 1, rc = lc | 1;
        inter(l, mid, lc, x, y);
        inter(mid + 1, r, rc, x, y);
        poly2[k] = new i64[len[k] = std::max(len[lc] + r - (mid + 1) + 2 - 1, len[rc] + mid - l + 2 - 1)];
        memset(poly2[k], 0, sizeof(i64) * len[k]);
        mul(len[lc], poly2[lc], r - (mid + 1) + 2, poly[rc], poly2[k]);
        add_mul(len[rc], poly2[rc], mid - l + 2, poly[lc], poly2[k]);
        return;
    }

    inline void inter_del(int l, int r, i64 k) {
        delete poly[k];
        delete poly2[k];
        if(l == r) {
            return;
        }
        int mid = l + r >> 1;
        inter_del(l, mid, k << 1);
        inter_del(mid + 1, r, (k << 1) | 1);
        return;
    }

    inline void inter(int n, i64 *x, i64 *y, i64 *a) {
        i64 *X = new i64[n], *Y = new i64[n], *A = new i64[n + 1];
        memcpy(X, x, sizeof(i64) * n);
        memcpy(Y, y, sizeof(i64) * n);
        eval_init(0, n - 1, 1, X);
        memcpy(A, poly[1], sizeof(i64) * (n + 1));
        der(n + 1, A, A);
        eval(n, A, 0, n - 1, 1, X, Y);
        for (int i = 0; i < n; ++i) {
            Y[i] = (long long) pow_mod(Y[i], mod - 2) * y[i] % mod;
        }
        inter(0, n - 1, 1, X, Y);
        memcpy(a, poly2[1], sizeof(i64) * n);
        inter_del(0, n - 1, 1);
        delete X;
        delete Y;
        delete A;
        return;
    }
};

const i64 maxn = (1 << 17) | 10, proot = 3, mod = 65537;
static polynomial<maxn, proot, mod> poly;
static i64 xs[maxn], y[maxn], a[maxn];
// --- END ---

#define NMAX 30
#define DMAX 16000
#define MOD 65537

static int x, n;
static i64 P[NMAX + 10][DMAX + 10];
static i64 cnt[NMAX + 10][MOD];
static char buf[DMAX + 10];

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

inline i64 inv(i64 n) {
    return n == 1 ? 1 : (MOD - MOD / n) * inv(MOD % n) % MOD;
}

inline void eval(int k) {
    int d = 0;
    for (; P[k][d]; d++) {
        a[d] = P[k][d];
    }
    reverse(a, a + d);
    for (int i = 0; i < x; i++) {
        xs[i] = i;
    }
    poly.eval(d, a, x, xs, y);
    for (int i = 0; i < x; i++) {
        if (y[i] < 0)
            y[i] += MOD;
    }
}

void initialize() {
    scanf("%d%d", &x, &n);

    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        for (int j = 0; buf[j]; j++) {
            P[i][j] = buf[j] - 'a' + 1;
        }
    }
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        eval(i);
        for (int j = 0; j < x; j++) {
            cnt[i][y[j]]++;
        }
    }

    i64 ans = n, xi = inv(x);
    for (int i = 0; i < MOD; i++) {
        i64 p = 1, e = 0;
        for (int j = 1; j <= n; j++) {
            add(e, cnt[j][i] * xi % MOD);
            p = p * (x - cnt[j][i]) % MOD * xi % MOD;
        }
        ans = (ans - e - p + 1) % MOD;
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
