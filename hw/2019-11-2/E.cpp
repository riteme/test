#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static i64 t[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", t + i);
    sort(t + 1, t + n + 1);
    i64 s = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        //printf("%lld, %lld\n", s, t[i]);
        if (s > t[i]) cnt++;
        else s += t[i];
    }
    printf("%lld\n", n - cnt);
    return 0;
}
