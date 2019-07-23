#include <cstdio>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

static int n, P, K;

int main() {
    scanf("%d%d%d", &n, &P, &K);
    unordered_map<i64, int> mp;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        i64 a;
        scanf("%lld", &a);
        a = (a*a%P*a%P - K)*a % P;
        if (a < 0) a += P;
        ans += mp[a];
        mp[a]++;
    }
    printf("%d\n", ans);
    return 0;
}
