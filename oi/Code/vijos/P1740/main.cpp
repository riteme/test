#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define WMAX 1000000

typedef long long int64;

static int n, m;
static int64 S;
static int64 w[NMAX + 10];
static int64 v[NMAX + 10];
static int lbound[NMAX + 10];
static int rbound[NMAX + 10];

static void initialize() {
    scanf("%d%d%lld", &n, &m, &S);

    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", w + i, v + i);
    }  // for

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", lbound + i, rbound + i);
    }  // for
}

static int64 wpre[NMAX + 10];
static int64 vpre[NMAX + 10];
static int64 evaluate(int64 W) {
    memset(wpre, 0, sizeof(wpre));
    memset(vpre, 0, sizeof(vpre));

    for (int i = 1; i <= n; i++) {
        if (w[i] >= W) {
            wpre[i] = 1;
            vpre[i] = v[i];
        }
    }  // for

    for (int i = 1; i <= n; i++) {
        wpre[i] += wpre[i - 1];
        vpre[i] += vpre[i - 1];
    }  // for

    int64 answer = 0;
    for (int i = 1; i <= m; i++) {
        int left = lbound[i];
        int right = rbound[i];

        answer +=
            (wpre[right] - wpre[left - 1]) * (vpre[right] - vpre[left - 1]);
    }  // for

    return answer;
}

int main() {
    initialize();

    int left = 1, right = WMAX;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        int64 answer = evaluate(mid);
        // printf("evaluate(%d) = %lld\n", mid, answer);
        if (answer < S)
            right = mid;
        else
            left = mid;
    }  // while

    if (left != right && evaluate(right) >= S)
        left = right;

    printf("%lld\n", min(abs(evaluate(left) - S), abs(evaluate(left + 1) - S)));

    return 0;
}  // function main
