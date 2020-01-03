#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    int n;
    scanf("%d", &n);
    i64 s[2] = {0};
    for (int i = 0; i < n; i++) {
        i64 m;
        scanf("%lld", &m);

        int b = i & 1;
        s[b] += m / 2;
        s[b ^ 1] += (m + 1) / 2;
    }
    printf("%lld\n", min(s[0], s[1]));

    return 0;
}
