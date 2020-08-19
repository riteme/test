#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 n;
    while (scanf("%lld", &n) != EOF) {
        i64 cnt = 0;
        for (int i = 0; i < 60; i++) {
            cnt += (n >> i) & 1;
        }
        i64 ans = 1LL << cnt;
        printf("%lld\n", ans);
    }
    return 0;
}
