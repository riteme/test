#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 500000;

int n;
int a[NMAX + 10];
int R[NMAX + 10];

int parse(int i) {
    if (a[i] != 1)
        return i + 1;
    int i0 = i;
    int j = 1;
    while (i <= n) {
        if (a[i] == j) {
            i++;
            j++;
        } else if (a[i] == 1) {
            i = parse(i);
        } else {
            break;
        }
    }
    if (a[i0] == 1)
        R[i0] = i;
    return i;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i = parse(i)) {

    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1)
            ans += R[i] - i;
    }
    printf("%lld\n", ans);
    return 0;
}