#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

static int n;
static char a[64];
static int b[10000000];

int main() {
    scanf("%d%s", &n, a);
    for (int s = 0; s < (1 << n); s++) {
        int sum = 0;
        for (int i = 0; i < n; i++) if ((s >> i) & 1)
            sum += a[i];
        b[s] = sum;
    }
    sort(b, b + (1 << n));
    for (int i = 0; i < (1 << n); i++)
        printf("%d ", b[i]);
    return 0;
}
