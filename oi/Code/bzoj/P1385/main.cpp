#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long int64;

inline int64 gcd(int64 a, int64 b) {
    while (b) {
        int64 tmp = b;
        b = a % b;
        a = tmp;
    }  // while
    return a;
}

#define NMAX 10000

static int n;
static int64 seq[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        seq[2] /= gcd(seq[1], seq[2]);
        int p = 3;
        while (p <= n && seq[2] != 1)
            seq[2] /= gcd(seq[2], seq[p++]);

        puts(seq[2] == 1 ? "YES" : "NO");
    }

    return 0;
}  // function main
