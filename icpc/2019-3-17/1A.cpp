#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

int main() {
    int n, c[16] = {0};
    scanf("%d", &n);
    int ans = 0, last = -1;
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        if (v != last) c[v] = 0;
        c[v]++;
        last = v;
        ans = max(ans, min(c[1], c[2]));
    }
    printf("%d\n", ans << 1);
    return 0;
}
