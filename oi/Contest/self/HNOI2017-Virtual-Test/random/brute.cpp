#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long i64;

#define NMAX 10

static int n;
static i64 s, p;
static i64 coeff[NMAX + 10];
static unordered_map<i64, int> seq;

inline i64 eval(i64 x) {
    i64 ret = 0;
    i64 a = 1;
    for (int i = 0; i <= n; i++) {
        ret = (ret + a * coeff[i]) % p;
        a = a * x % p;
    }  // for

    return ret;
}

void initialize() {
    scanf("%d%lld%lld", &n, &s, &p);
    for (int i = 0; i <= n; i++) {
        scanf("%lld", coeff + i);
    }  // for
}

int main() {
    initialize();
    seq[s] = 0;
    printf("%lld ", s);
    for (int i = 1; true; i++) {
        s = eval(s);
        printf("%lld ", s);

        if (seq.count(s)) {
            printf("\n%d", i - seq[s]);
            break;
        }

        seq[s] = i;
    }  // for

    return 0;
}  // function main
