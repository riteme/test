#include <cstdio>
#include <cstring>
#include <climits>

#include <map>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000000

static int n;
static i64 seq[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }
}

static int pcnt;
static i64 prime[NMAX + 10];

void factor(i64 x) {
    for (i64 i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            prime[++pcnt] = i;
            while (x % i == 0)
                x /= i;
        }
    }

    if (x)
        prime[++pcnt] = x;
}

inline i64 gcd(i64 a, i64 b) {
    while (b) {
        i64 t = a % b;
        a = b;
        b = t;
    }

    return a;
}

int main() {
    initialize();

    factor(seq[1]);

    for (int i = 1; i <= n; i++) {
        i64 r = gcd(seq[1], seq[i]);

        if (r == 1)
            printf("-1 ");
        else {
            for (int i = 1; i <= pcnt; i++) {
                if (r % prime[i] == 0) {
                    printf("%lld ", r / prime[i]);
                    break;
                }
            }
        }
    }
    puts("");

    return 0;
}
