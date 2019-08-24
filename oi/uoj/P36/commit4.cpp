#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define SMAX 64
#define KMAX 5

typedef unsigned long long uint64;

static int S;
static int n, k;
static uint64 seq[NMAX + 10];
static uint64 X[SMAX + 10];
static bool exist[SMAX + 10];

inline void add(uint64 x, uint64 *dest, int s) {
    for (int i = s - 1; i >= 0; i--) {
        if ((x >> i) & 1) {
            if (dest[i])
                x ^= dest[i];
            else {
                dest[i] = x;
                break;
            }
        }
    }
}

static void initialize() {
    scanf("%d%d", &n, &k);

    switch (k) {
        case 1: S = 64; break;
        case 2: S = 32; break;
        case 3: S = 22; break;
        case 4: S = 17; break;
        case 5: S = 14; break;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%llu", seq + i);
        
        for (int p = 0; p < S; p++) {
            if ((seq[i] >> p) & 1)
                exist[p] = true;
        }

        add(seq[i], X, S);
    }
}

#define OFFEST SMAX

static int pos[KMAX + 10];
static uint64 equ[SMAX + 10];
static uint64 answer[SMAX * 2 + 10];

static int solve() {
    memset(equ, 0, sizeof(equ));

    for (int i = 1; i <= k; i++) {
        int p = pos[i];

        uint64 v = 0;
        for (int j = 0; j < S; j++) {
            v |= ((X[j] >> p) & 1) << j;
        }

        add(v, equ, S);
    }

    int cnt = 0;
    for (int i = 0; i < S; i++) {
        if (equ[i])
            cnt++;
    }

    return cnt;
}

static void multiply(int id, int sum) {
    if (id > k) {
        assert(sum < SMAX);
        int c = solve();
        assert(c > 0);

        answer[sum - c + OFFEST]++;
    } else {
        for (int i = 0; i < S; i++) {
            if (exist[i]) {
                pos[id] = i;
                multiply(id + 1, sum + i);
            }
        }
    }
}

// Fuck

static int m;

static void select(int s) {
    uint64 v = 0;
    for (int i = 0; i < m; i++) {
        if ((s >> i) & 1) {
            v ^= X[i];
        }
    }

    assert(v < (1 << (S - 1)));

    uint64 ret = v;
    for (int i = 1; i < k; i++) {
        ret *= v;
    }

    for (int i = 0; i < SMAX; i++) {
        answer[i - m + OFFEST] += (ret >> i) & 1;
    }
}

static bool cmp(const uint64 a, const uint64 b) {
    return a > b;
}

static bool test(int p) {
    for (int i = 1; i <= n; i++) {
        if ((seq[i] >> p) & 1)
            return true;
    }
    return false;
}

int main() {
    initialize();

    if (k <= 2)
        multiply(1, 0);
    else {
        if (k == 5 && test(12))
            multiply(1, 0);
        else {
            sort(X, X + SMAX, cmp);
            while (X[m])
                m++;

            for (int s = 0; s < (1 << m); s++) {
                select(s);
            }
        }
    }

    uint64 expect = 0;
    for (int i = -SMAX; i < SMAX; i++) {
        int p = i + OFFEST;

        if (answer[p] > 1) {
            answer[p + 1] += answer[p] >> 1;
            answer[p] &= 1;
        }

        if (i >= 0)
            expect += answer[p] << i;
    }

    printf("%llu", expect);
    if (answer[OFFEST - 1])
        printf(".5");
    printf("\n");

    return 0;
}
