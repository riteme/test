#include <cstdio>

#include <algorithm>

typedef long long i64;

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    i64 t = 0;
    for (int i = 0; i < n; i++) {
        i64 x, L;
        scanf("%lld%lld", &x, &L);
        t = max(t, x) + L;
    }
    printf("%lld\n", t);
    return 0;
}