#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100000
// #define NMAX 100
#define LOGN 17

typedef long long int64;

static int n;
static int64 seq[NMAX + 10];
static int64 st[NMAX + 10][LOGN + 1];

static bool cmp(const int a, const int b) {
    return seq[a] < seq[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }  // for

    for (int i = 1; i <= n; i++) {
        st[i][0] = i;
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= (n - (1 << j) + 1); i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1], cmp);
        }  // for
    }      // for
}

inline int64 query(int left, int right) {
    if (left == right)
        return left;

    int k = 0;
    while ((1 << (k + 1)) <= (right - left)) {
        k++;
    }  // while

    return min(st[left][k], st[right - (1 << k) + 1][k], cmp);
}

static int64 solve(int left, int right, int64 removed) {
    if (right < left)
        return 0;
    if (left == right)
        return seq[left] - removed;

    int mid = query(left, right);
    return solve(left, mid - 1, seq[mid]) + solve(mid + 1, right, seq[mid]) +
           seq[mid] - removed;
}

int main() {
    initialize();
    printf("%lld\n", solve(1, n, 0));

    return 0;
}  // function main
