#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, K;
char t[2][NMAX + 10];

int calc(int f, int i) {
    int ret = 0;
    for (int j = 0; j < 2; j++)
    for (int k = 1; k <= n; k++) if (t[j][k] == '1') {
        if (f == j) ret = max(ret, abs(i - k));
        else ret = max(ret, i + k + K);
    }
    return ret;
}

int main() {
    scanf("%d%d%s%s", &n, &K, t[1] + 1, t[0] + 1);

    int mi = INT_MAX, x, y;
    for (int f = 0; f < 2; f++)
    for (int i = 1; i <= n; i++) {
        int v = calc(f, i);
        if (v < mi) {
            mi = v;
            x = f;
            y = i;
        }
    }

    printf("%d\n%d %d\n", mi, x + 1, y);
    return 0;
}