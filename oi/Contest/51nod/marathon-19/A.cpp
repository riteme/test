#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 30
#define MOD 1000000007

typedef long long int64;

static int n;
static int64 seq[NMAX + 10]
static int next[NMAX + 10][LOGN + 1];
static int onelast[LOGN + 1];
static int zerolast[LOGN + 1];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int64 x;
        scanf("%lld", &x);

        seq[i] = x;

        for (int j = 0; j <= LOGN; j++) {
            int bit = (x >> j) & 1;
        }
    }
}

int main() {
    initialize();

    return 0;
}
