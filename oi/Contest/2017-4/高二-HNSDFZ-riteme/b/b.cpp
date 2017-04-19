#define NDEBUG

#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>
#include <cstdlib>
#include <ctime>

#include <random>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200
#define TMAX 5000

void gen1(int *P) {
    for (int i = 1; i <= NMAX; i++) {
        P[i] = i;
    }

    for (int i = 1; i <= NMAX; i++) {
        int p = rand() % NMAX + 1;
        swap(P[i], P[p]);
    }
}

void gen2(int *P) {
    for (int i = 1; i <= NMAX; i++) {
        P[i] = i;
    }

    for (int i = 1; i <= NMAX; i++) {
        int p = rand() % i + 1;
        swap(P[i], P[p]);
    }
}

i64 dist(int *D1, int *D2) {
    i64 ret = 0;

    for (int i = 1; i <= NMAX; i++) {
        i64 delta = D1[i] - D2[i];
        ret += delta * delta;
    }

    return ret;
}

static int T;
static int sample1[TMAX + 10][NMAX + 10];
static int sample2[TMAX + 10][NMAX + 10];

i64 val1(int *D) {
    i64 ret = 0;

    for (int i = 1; i <= TMAX; i++) {
        ret += dist(&sample1[i][0], D);
    }

    return ret;
}

i64 val2(int *D) {
    i64 ret = 0;

    for (int i = 1; i <= TMAX; i++) {
        ret += dist(&sample2[i][0], D);
    }

    return ret;
}

i64 judge(int *P) {
    int cnt = 0;
    for (int i = 1; i <= NMAX; i++) {
        if (i == P[i])
            cnt++;
    }

    if (cnt >= 11)
        return 3;

    return val1(P) < val2(P) ? 1 : 2;
}

static int P[NMAX + 10];

void initialize() {
    scanf("%d", &T);

    for (int i = 1; i <= TMAX; i++) {
        gen1(&sample1[i][0]);
    }

    for (int i = 1; i <= TMAX; i++) {
        gen2(&sample2[i][0]);
    }
}

int main() {
#ifdef NDEBUG
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
#endif
    initialize();

    while (T--) {
        int _;
        scanf("%d", &_);
        for (int i = 1; i <= NMAX; i++) {
            scanf("%d", P + i);
        }

        printf("%lld\n", judge(P));
    }

    return 0;
}
