// sort before next_perumutation

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

static int n;
static int a[20];
static int b[20];

int main() {
    scanf("%d", &n);
    n *= 2;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        sum += a[i];
    }
    int ans = 0;
    sort(a, a + n);
    int T = 20000000;
    do {
        int s = 0, ret = INT_MAX;
        for (int i = n / 2; i < n; i++) s += a[i];
        for (int i = 0; i <= n; i++) {
            ret = min(ret, sum - s);
            s += a[i] - a[(i + n / 2) % n];
        }
        if (ret > ans) {
            ans = ret;
            memcpy(b, a, sizeof(b));
        }
    } while (T-- && next_permutation(a, a + n));
    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);
    puts("");
    //fprintf(stderr, "ans = %d\n", ans);
    return 0;
}
