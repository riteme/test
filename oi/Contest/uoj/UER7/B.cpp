#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int h[NMAX + 10];
static int answer[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", h + i);
}

inline void update(int i, int limit) {
    int maxv = h[i];
    int minv = h[i];

    for (int j = i - 1; j >= 1; j--) {
        if (i - j + 1 > limit)
            return;

        maxv = max(maxv, h[j]);
        minv = min(minv, h[j]);

        answer[i - j + 1] = min(answer[i - j + 1], maxv - minv);
    }  // for
}

int main() {
    initialize();

    for (int i = 2; i <= n; i++)
        answer[i] = INT_MAX;

    if (n <= 2000) {
        for (int i = 2; i <= n; i++)
            update(i, n + 10);
    } else {
        int BLOCKSIZE = sqrt(n);
        for (int i = n; i >= 2; i -= max(BLOCKSIZE >> 2, 1))
            update(i, n + 10);

        for (int i = 2; i <= n; i++)
            update(i, BLOCKSIZE << 2);
    }

    for (int i = 2; i <= n; i++)
        printf("%d\n", answer[i]);

    return 0;
}  // function main
