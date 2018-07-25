/**
 * commit4.cpp is passed temporary.
 * I need a better code to solve this problem.
 * 2016.12.23
 */

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
        case 3: S = 21; break;
        case 4: S = 16; break;
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

    for (int i = S - 1; i >= 0; i--) {
        if (X[i]) {
            for (int j = i - 1; j >= 0; j--) {
                if ((X[j] >> i) & 1)
                    X[j] ^= X[i];
            }
        }
    }
}

#define OFFEST SMAX

static uint64 equ[SMAX + 10];
static uint64 answer[SMAX * 2 + 10];

inline uint64 select(uint64 s) {
    uint64 ret = 0;
    for (int i = 0; i < S; i++) {
        if ((s >> i) & 1)
            ret ^= equ[i];
    }

    return ret;
}

static int solve(uint64 mask) {
    memset(equ, 0, sizeof(equ));

    for (int i = 0; i < S; i++) {
        add(X[i] & mask, equ, S);
    }

    for (int i = S - 1; i >= 0; i--) {
        if (equ[i]) {
            for (int j = i - 1; j >= 0; j--) {
                if ((equ[j] >> i) & 1)
                    equ[j] ^= equ[i];
            }
        }
    }

    int cnt = 0;
    uint64 sum = 0;
    for (int i = 0; i < S; i++) {
        if (equ[i]) {
            cnt++;
            sum ^= equ[i];
        }
    }

    if (sum == mask)
        return cnt;
    return 233;
}

static void multiply(int id, int sum, uint64 mask) {
    if (id > k) {
        int c = solve(mask);

        if (c != 233)
            answer[sum - c + OFFEST]++;
    } else {
        for (int i = 0; i < S; i++) {
            multiply(id + 1, sum + i, mask | (1ull << i));
        }
    }
}

int main() {
    initialize();

    multiply(1, 0, 0);

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
