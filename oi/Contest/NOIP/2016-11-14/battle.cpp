#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

static int n, k;
static int64 seq[NMAX + 10];
static int64 suma2;
static int64 suma;

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
        scanf("%lld", seq + i);
}

inline int64 evaluate(int x) {
    return suma2 + k * seq[x] * seq[x] - 2 * seq[x] * suma;
}

int main() {
    freopen("battle.in", "r", stdin);
    freopen("battle.out", "w", stdout);
    initialize();

    int64 answer = LLONG_MAX;
    for (int i = 1; i <= k; i++) {
        suma2 += seq[i] * seq[i];
        suma += seq[i];
    }

    int mid = 1;
    for (int i = 1; i <= n - k + 1; i++) {
        while (mid < n && evaluate(mid) >= evaluate(mid + 1))
            mid++;
        answer = min(answer, evaluate(mid));
        suma2 += seq[i + k] * seq[i + k] - seq[i] * seq[i];
        suma += seq[i + k] - seq[i];
    }

    printf("%lld\n", answer);

    return 0;
}
