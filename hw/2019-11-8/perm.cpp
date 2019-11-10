#include <cassert>
#include <cstdio>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, op;
static int p[NMAX + 10];
static int rk[NMAX + 10];

int main() {
    random_device rd;
    while (scanf("%d%d", &n, &op) != EOF) {
        for (int i = 1; i <= n; i++) p[i] = i;
        mt19937_64 gen(rd());
        int m = op * n;
        if (op == 7) m++;
        while (m--) {
            int i = gen() % (n - 1) + 1;
            int j = gen() % (n - i) + i + 1;
            assert(1 <= i && i < j && j <= n);
            swap(p[i], p[j]);
        }
        for (int i = 1; i <= n; i++)
            rk[p[i]] = i;
        i64 sum = 0;
        i64 cnt = 0;
        for (int i = 1; i <= n; i++) {
            sum += abs(rk[i] - i);
            cnt += rk[i] == i;
        }
        //printf("sum = %lld, cnt = %lld\n", sum, cnt);
        printf("%d\n", n);
        for (int i = 1; i <= n; i++)
            printf("%d ", p[i]);
    }
    return 0;
}
