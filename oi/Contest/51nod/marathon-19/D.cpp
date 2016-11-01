#include <cstdio>

#define NMAX 500000

typedef long long int64;

static int n;
static int aseq[NMAX + 10];
static int64 apre[NMAX + 10][3];
static int bseq[NMAX + 10];
static int64 bpre[NMAX + 10][3];

static int64 query_a(int left

static int64 evaluate_a(int limit) {
    int64 cycle = 0;
    
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        aseq[i] = x;
        apre[i][x] = 1;
        apre[i][0] += apre[i - 1][0];
        apre[i][1] += apre[i - 1][1];
        apre[i][2] += apre[i - 1][2];
    }

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        bseq[i] = x;
        bpre[i][x] = 1;
        bpre[i][0] += bpre[i - 1][0];
        bpre[i][1] += bpre[i - 1][1];
        bpre[i][2] += bpre[i - 1][2];
    }

    return 0;
}
