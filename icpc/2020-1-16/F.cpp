#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

int sgn(int x) {
    return x == 0 ? 0 : (x > 0 ? 1 : -1);
}

int n;
int a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        a[i] = sgn(v);
    }

    i64 ap = 0, az = 0, an = 0;
    i64 cp = 1, cn = 0, cz = 0, pr = 1;
    for (int i = 1; i <= n; i++)
    if (a[i]) {
        pr *= a[i];

        if (pr > 0) {
            ap += cp;
            an += cn;
            az += cz;
            cp++;
        } else {
            ap += cn;
            an += cp;
            az += cz;
            cn++;
        }
    } else {
        az += i;
        cz = i;
        cp = 1;
        cn = 0;
        pr = 1;
    }

    printf("%lld %lld %lld\n", an, az, ap);
    return 0;
}