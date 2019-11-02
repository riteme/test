#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define AMAX 1000000000000000
#define MMAX 2000000
//#define NMAX 300000
#define NMAX 200000

static int m;
static i64 mem[MMAX + 10], t[NMAX + 10];
static int lg[NMAX + 10], k[NMAX + 10];
static i64 pw[100];

int expo(i64 a, int al, i64 b, int bl) {
    int r = al + bl;
    a = a * b / pw[r];
    return lg[a] + r;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i <= 50; i++)
        pw[i] = pw[i - 1] * 10;
    for (int i = 10; i <= NMAX; i++)
        lg[i] = lg[i / 10] + 1;

    for (i64 a = 1; a <= NMAX; a++)
    for (int l = 2; l <= 15; l++)
    for (i64 q = 1; ; q++) {
        int i;
        t[l] = a;
        k[l] = lg[a];
        for (i = 1; i <= l; i++) {
            t[l - i] = t[l - i + 1] * q;
            if (t[l - i] > NMAX) break;
            k[l - i] = expo(t[l - i + 1], k[l - i + 1], q, lg[q]);
        }
        if (i <= l) break;
        for (i64 p = q + 1; ; p++) {
            i64 A = 0, pr = 1, pt = 0;
            int len = 0;
            //printf("p = %lld\n", p);
            for (i = 0; A <= AMAX && len <= 15 && i <= l; pr *= p, i++) {
                i64 b = t[i] * pr;
                //if (b > NMAX) break;
                int bexp = expo(t[i], k[i], pr, pt);
                if (bexp > 15) break;
                //printf("bexp = %d, pr = %lld\n", bexp, pr);
                A = A * pw[bexp + 1];
                if (A < 0) break;
                A += b;
                len += bexp + 1;
                pt = expo(pr, pt, p, lg[p]);
            }
            if (i <= l || len > 15) break;
            //printf("[%d, %lld] a = %lld, p = %lld, q = %lld: %lld\n", l, t[0], a, p, q, A);
            mem[m++] = A;
        }
    }
    fprintf(stderr, "m = %d\n", m);
    sort(mem, mem + m);
    m = unique(mem, mem + m) - mem;
    //for (int i = 0; i < m; i++)
    //    printf("%lld\n", mem[i]);
    fprintf(stderr, "m = %d\n", m);

    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        i64 L, R;
        scanf("%lld%lld", &L, &R);
        auto lt = lower_bound(mem, mem + m, L);
        auto rt = upper_bound(mem, mem + m, R);
        i64 ans = rt - lt;
        printf("Case #%d: %lld\n", _t, ans);
    }
    return 0;
}
