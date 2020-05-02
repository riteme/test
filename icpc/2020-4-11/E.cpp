#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 ans = 0, sum = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        i64 v;
        scanf("%lld", &v);
        sum += v;
        ans = min(ans, sum);
    }

    printf("%lld\n", -ans);
    return 0;
}