#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

int n;
i64 a[100000];

int main() {
    i64 m;
    scanf("%lld", &m);
    for (i64 x = m; x; x = (x - 1) & m) {
        a[n++] = x;
    }
    for (int i = n; i >= 0; i--) {
        printf("%lld\n", a[i]);
    }
    return 0;
}
