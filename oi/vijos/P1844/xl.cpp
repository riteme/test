#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 17

static int n;
static int seq[NMAX + 10];
static int st[NMAX + 10][LOGN + 1];
static int _high[NMAX + 10];

static bool cmp(const int a, const int b) {
    return seq[a] < seq[b];
}

inline int highbit(int x) {
    if (_high[x] >= 0)
        return _high[x];

    for (int i = LOGN; i >= 0; i--) {
        if ((x >> i) & 1) {
            _high[x] = i;

            return i;
        }
    }

    return 0;
}

inline int query(int left, int right) {
    if (left == right)
        return left;

    int k = highbit(right - left + 1);
    return min(st[left][k], st[right - (1 << k) + 1][k], cmp);
}

static int solve(int left, int right, int sum) {
    if (right < left)
        return 0;

    int mid = query(left, right);

    return seq[mid] - sum
           + solve(left, mid - 1, seq[mid])
           + solve(mid + 1, right, seq[mid]);
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        st[i][0] = i;
    }

    for (int i = 1; i <= n; i++)
        _high[i] = -1;

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << (j - 1)) <= n)
                st[i][j] = min(
                    st[i][j - 1],
                    st[i + (1 << (j - 1))][j - 1],
                    cmp
                );
            else
                st[i][j] = st[i][j - 1];
        }
    }
}

int main() {
    initialize();

    printf("%d\n", solve(1, n, 0));

    return 0;
}
